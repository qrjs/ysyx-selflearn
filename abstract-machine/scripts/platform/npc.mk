# 定义AM源文件
AM_SRCS := riscv/npc/start.S \
           riscv/npc/trm.c \
           riscv/npc/ioe.c \
           riscv/npc/timer.c \
           riscv/npc/input.c \
           riscv/npc/cte.c \
           riscv/npc/trap.S \
           platform/dummy/vme.c \
           platform/dummy/mpe.c

# 编译标志，启用数据段和函数段优化
CFLAGS    += -fdata-sections -ffunction-sections
# 链接标志，指定链接脚本和内存布局
LDFLAGS   += -T $(AM_HOME)/scripts/linker.ld \
						 --defsym=_pmem_start=0x80000000 --defsym=_entry_offset=0x0
# 链接标志，启用段清理和指定入口点
LDFLAGS   += --gc-sections -e _start
# 不导出编译和链接标志
unexport CFLAGS
unexport LDFLAGS

# 旧版NPC参数(使用-f加载ELF文件)，现已注释
# NPCFLAGS += -l $(shell dirname $(IMAGE).elf)/npc-log.txt -b -f $(IMAGE).elf

# 当前NPC参数(使用-e加载ELF文件)
# 禁用 DiffTest，只使用基本参数
NPCFLAGS += -b -e $(IMAGE).elf

# 添加主参数到编译标志
CFLAGS += -DMAINARGS=\"$(mainargs)\"
.PHONY: $(AM_HOME)/am/src/riscv/npc/trm.c

# 生成二进制镜像文件
image: $(IMAGE).elf
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

# 运行目标：在NPC上运行程序
run: image
	@echo "Running $(IMAGE_REL) on NPC..."
	@$(MAKE) -C $(NPC_HOME) run ARGS="$(NPCFLAGS)" IMG=$(IMAGE).bin > $(IMAGE).npc.log 2>&1; \
	RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		echo "NPC execution failed with code $$RESULT (check $(IMAGE).npc.log for details)"; \
		grep -A 5 "difftest.*nopass\|ABORT" $(IMAGE).npc.log; \
	fi; \
	if grep -q "ABORT\|HIT BAD TRAP" $(IMAGE).npc.log; then \
		echo "Program execution aborted or hit bad trap (check $(IMAGE).npc.log for details)"; \
		exit 1; \
	fi

# GDB调试目标
gdb: image
	$(MAKE) -C $(NPC_HOME) gdb ARGS="$(NPCFLAGS)" IMG=$(IMAGE).bin