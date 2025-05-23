# 包含主项目Makefile
include $(YSYX_HOME)/Makefile

# 顶层模块名称
MODULE=rv32

# 查找所有C++源文件，排除我们将替换的文件
CSRCS = $(shell find $(abspath ./csrc) -name "*.cpp" -not -name "tb_rv32.cpp" -not -name "tb_rv32_new.cpp")
# 添加我们的自定义文件
CSRCS += $(abspath ./csrc/ebreak_new.cpp)
CSRCS += $(abspath ./csrc/tb_rv32_new.cpp)

# 查找所有Verilog源文件
#VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
VSRCS += $(shell find $(abspath ./vsrc/*) -name "*.v")

# 包含路径
INC_PATH = $(NPC_HOME)/include/

# 链接库
LIBS = -lreadline   # 链接readline库(用于命令行编辑)
LIBS += -ldl        # 链接dlfcn库(用于动态加载)
#LIBS += $(shell llvm-config-11 --libs)
#CXXFLAGS += $(shell llvm-config-11 --cxxflags) -fPIE


# DiffTest相关设置
# ifdef CONFIG_DIFFTEST
DIFF_REF_PATH = $(NEMU_HOME)
DIFF_REF_SO = $(DIFF_REF_PATH)/build/riscv32-nemu-interpreter.so
ARGS_DIFF = --diff=$(DIFF_REF_SO)

# 程序镜像，由AM Makefile(npc.mk)加载
IMG ?=      #loaded by AM Makefile (npc.mk)

# 默认参数设置，指定日志文件位置
override ARGS ?= --log=./log/npc-log.txt
# 注释掉下面这行以禁用 DiffTest
# override ARGS += $(ARGS_DIFF)

# 最终生成的可执行文件
BINARY := ./obj_dir/V$(MODULE)
# 运行命令
NEMU_EXEC := $(BINARY) $(ARGS) $(IMG)

# endif


# 运行目标：编译并运行NPC
.PHONY:run
run:$(VSRCS) $(CSRCS)
	$(call git_commit, "NPC Simulation Update")   # DO NOT REMOVE THIS LINE!!!
	rm -rf .stamp.*;
	rm -rf ./obj_dir
	rm -rf waveform.fst
	@echo "### VERILATING ###"
	verilator --trace-fst --top-module $(MODULE) -cc $(VSRCS) --exe $(CSRCS) -I$(INC_PATH) -I$(INC_PATH)/verilator
	@echo "LIBS +=$(LIBS)" >> ./obj_dir/V$(MODULE).mk
	@echo "### BUILDING SIM ###"
	make -C obj_dir -f V$(MODULE).mk V$(MODULE)
	@echo "### SIMULATING ###"
	@$(NEMU_EXEC); exit_code=$$?; \
	if [ $$exit_code -ne 0 ]; then \
		echo "错误: NPC执行返回非零值: $$exit_code"; \
		exit $$exit_code; \
	fi
	
# 波形查看目标
.PHONY:wave
wave: 
	@echo "### WAVES ###"
	surfer waveform.fst

