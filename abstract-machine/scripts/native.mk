AM_SRCS := native/trm.c \
           native/ioe.c \
           native/cte.c \
           native/trap.S \
           native/vme.c \
           native/mpe.c \
           native/platform.c \
           native/ioe/input.c \
           native/ioe/timer.c \
           native/ioe/gpu.c \
           native/ioe/uart.c \
           native/ioe/audio.c \
           native/ioe/disk.c \

CFLAGS  += -fpie $(shell sdl2-config --cflags)
ASFLAGS += -fpie -pie
comma = ,
LDFLAGS_CXX = $(addprefix -Wl$(comma), $(NPC_LDFLAGS)) -pie -ldl $(shell sdl2-config --libs)
image:
	@echo + LD "->" $(IMAGE_REL)
	# 链接生成 NPC 可执行程序，使用 NPC_LDFLAGS（不含 -melf 选项）
	@g++ -pie -o $(IMAGE) \
	    -Wl,--whole-archive $(LINKAGE) -Wl,-no-whole-archive $(LDFLAGS_CXX) \
	    -lSDL2 -ldl
run: image
	$(IMAGE).elf

gdb: image
	gdb -ex "handle SIGUSR1 SIGUSR2 SIGSEGV noprint nostop" $(IMAGE).elf
