#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h"
#include "verilated_fst_c.h"
#include "Vtop__Dpi.h"
#include "svdpi.h"

#define HIT_GOOD_TRAP 1
#define HIT_BAD_TRAP  2
#define ABORT         3

VerilatedFstC* tfp = new VerilatedFstC();
Vtop *top = new Vtop("top");
vluint64_t main_time = 0;

// 指令存储器 (地址对齐检查增强)
static const uint32_t inst[] = {
  0xffc10113,    // addi sp,sp,-4
  0x06400593,    // li a1,100
  0x06458613,    // add a2,a1,100
  0x0c860693,    // add a3,a2,200
  0xed468713,    // add a4,a3,-300
  0xe7070793,    // add a5,a4,-400
  0x80178813,    // add a6,a5,-2047
  0x7fa80893,    // add a7,a6,2042
  0x00100073,    // ebreak (Good Trap)
};

static uint32_t pmem_read(uint32_t pc) {
  if (pc < 0x80000000) return 0;
  uint32_t index = (pc - 0x80000000) >> 2;
  return (index < sizeof(inst)/4) ? inst[index] : 0;
}

// DPI函数
extern "C" void ebreak(int status, int inst_val) {
  const char* color = "1;31m";
  const char* msg = "UNKNOWN";
  const char* color_r= "1;31m";

  switch (status) {
    case HIT_GOOD_TRAP:
      color = "1;32m"; msg = "GOOD TRAP";
      break;
    case HIT_BAD_TRAP:
      color = "1;31m"; msg = "BAD TRAP";
      break;
    case ABORT:
      color = "1;35m"; msg = "ABORT";
      break;
  }

  printf("\033[%s HIT %s \033[0m at \033[%s pc \033[0m = 0x%08x   \033[%s Instruction \033[0m = 0x%08x\n",
         color, msg, color ,top->pc,color, inst_val);
  Verilated::gotFinish(true);
}

// 单周期驱动
static void single_cycle() {
  if (Verilated::gotFinish()) return;

  top->clk = 0;
  top->eval();
  if (Verilated::gotFinish()) return;
  tfp->dump(main_time++);

  top->clk = 1;
  top->eval();
  if (Verilated::gotFinish()) return;
  tfp->dump(main_time++);

  if (!Verilated::gotFinish()) {
    top->inst = pmem_read(top->pc);
  }
}

// 复位逻辑
static void reset(int cycles = 5) {
  top->rst = 1;
  while (cycles-- > 0) single_cycle();
  top->rst = 0;
  assert((top->pc & 0x3) == 0 && "PC misaligned!");
}

int main() {
  Verilated::traceEverOn(true);
  
  top->trace(tfp, 99);
  tfp->open("waveform.fst");

  reset();

  while (!Verilated::gotFinish()) {
    single_cycle();
    if (main_time++ > 1000) {
      printf("\033[1;33mTimeout!\033[0m\n");
      Verilated::gotFinish(true);
    }
  }

  tfp->close();
  delete top;
  delete tfp;
  printf("Simulation completed.\n");
  return 0;
}