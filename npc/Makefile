MODULE=top
CSRCS = $(shell find $(abspath ./csrc) -name "*.cpp")
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
VSRCS += $(shell find $(abspath ./vsrc/*) -name "*.v")

# 包含通用Makefile规则
include ../Makefile


.PHONY: sim
sim: waveform.fst
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Simulation completed"

.PHONY: verilate
verilate: .stamp.verilate

.PHONY: build
build: obj_dir/V$(MODULE)

.PHONY: wave
wave: waveform.fst
	@echo
	@echo "### WAVES ###"
	gtkwave waveform.fst

waveform.fst: ./obj_dir/V$(MODULE)
	@echo
	@echo "### SIMULATING ###"
	@./obj_dir/V$(MODULE)

./obj_dir/V$(MODULE): .stamp.verilate
	@echo
	@echo "### BUILDING SIM ###"
	$(MAKE) -C obj_dir -f V$(MODULE).mk V$(MODULE)

# 修改verilate目标
.stamp.verilate: $(VSRCS) $(CSRCS)
	@echo
	@echo "### VERILATING ###"
	verilator -Wno-STMTDLY -Wno-MODDUP --trace --trace-fst --top-module $(MODULE) \
		-cc $(VSRCS) --exe $(CSRCS) \
		-CFLAGS "-std=c++17 -O3"  # 新增C++17支持
	@touch .stamp.verilate

.PHONY: lint
lint: $(MODULE).v
	verilator --lint-only $(MODULE).v

.PHONY: clean
clean:
	rm -rf .stamp.*
	rm -rf ./obj_dir
	rm -rf waveform.fst
	