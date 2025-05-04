include $(YSYX_HOME)/Makefile
MODULE=rv32
CSRCS = $(shell find $(abspath ./csrc) -name "*.cpp")
#VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
VSRCS += $(shell find $(abspath ./vsrc/*) -name "*.v")
INC_PATH = $(NPC_HOME)/include/
LIBS = -lreadline   # link the <readline> lib
LIBS += -ldl        # link the <dlfcn> lib
#LIBS += $(shell llvm-config-11 --libs)
#CXXFLAGS += $(shell llvm-config-11 --cxxflags) -fPIE


# ifdef CONFIG_DIFFTEST
DIFF_REF_PATH = $(NEMU_HOME)
DIFF_REF_SO = $(DIFF_REF_PATH)/build/riscv32-nemu-interpreter.so
#ARGS_DIFF = --diff=$(DIFF_REF_SO)

IMG ?=      #loaded by AM Makefile (npc.mk)

override ARGS ?= --log=./log/npc-log.txt
#override ARGS += $(ARGS_DIFF)
BINARY := ./obj_dir/V$(MODULE)
NEMU_EXEC := $(BINARY) $(ARGS) $(IMG)

# endif



.PHONY:run
run:$(VSRCS) $(CSRCS)
	$(call git_commit, "NPC Simulation Update")   # DO NOT REMOVE THIS LINE!!!
	rm -rf .stamp.*;
	rm -rf ./obj_dir
	rm -rf waveform.fst
	@echo "### VERILATING ###"
	verilator --trace-fst --top-module $(MODULE) -cc $(VSRCS) --exe $(CSRCS) -I$(INC_PATH)
	@echo "LIBS +=$(LIBS)" >> ./obj_dir/V$(MODULE).mk  
	@echo "### BUILDING SIM ###"
	make -C obj_dir -f V$(MODULE).mk V$(MODULE) $(DIFF_REF_PATH) -o $(abspath $(BINARY))
	@echo "### SIMULATING ###"
	@$(NEMU_EXEC)
	
.PHONY:wave
wave: 
	@echo "### WAVES ###"
	gtkwave waveform.fst

