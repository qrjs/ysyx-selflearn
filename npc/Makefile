TOPNAME = top
NXDC_FILES = constr/top.nxdc
INC_PATH ?=

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build --trace -cc \
                    -O3 --x-assign fast --x-initial fast --noassert

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)  # 最终生成的可执行文件

# 默认目标
default: $(BIN)

# 创建 build 文件夹
$(shell mkdir -p $(BUILD_DIR))

# 生成引脚绑定文件
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@  # 自动生成引脚绑定

# 获取所有 Verilog 文件和 C/C++ 源文件
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)

# 包含 NVBoard 编译规则
include $(NVBOARD_HOME)/scripts/nvboard.mk

# Verilator 编译选项
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
LDFLAGS += -lSDL2 -lSDL2_image

# 仿真指令：编译生成可执行文件
$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR) wave.vcd  # 清除之前的编译文件和波形文件
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

# 默认目标：编译并运行
ll: default

# 运行仿真
run: $(BIN)
	./build/top +trace  # 执行生成的仿真可执行文件
	@$(call git_commit, "sim RTL")  # Git 追踪仿真记录

# 清理目标
clean:
	rm -rf $(BUILD_DIR) wave.vcd

.PHONY: default all clean run

