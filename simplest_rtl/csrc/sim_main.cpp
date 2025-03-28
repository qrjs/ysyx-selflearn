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
static bool trap_triggered = false; // 新增标志位

static const uint32_t inst[] = {
  0xffc10113, 0x06400593, 0x06458613, 0x0c860693,
  0xed468713, 0xe7070793, 0x80178813, 0x7fa80893,
  0x00100073
};

static uint32_t pmem_read(uint32_t pc) {
  if (pc < 0x80000000) return 0;
  uint32_t index = (pc - 0x80000000) >> 2;
  return (index < sizeof(inst)/4) ? inst[index] : 0;
}

extern "C" void ebreak(int status, int inst_val) {
  if (trap_triggered) return; // 防止重复触发
  
  const char* color = "1;31m";
  const char* msg = "UNKNOWN";
  switch (status) {
    case HIT_GOOD_TRAP: color = "1;32m"; msg = "GOOD TRAP"; break;
    case HIT_BAD_TRAP:  color = "1;31m"; msg = "BAD TRAP";  break;
    case ABORT:         color = "1;35m"; msg = "ABORT";     break;
  }
  printf("\033[%s HIT %s \033[0m at \033[%s pc\033[0m = 0x%08x,\033[%s inst\033[0m = 0x%08x\n",
         color, msg, color,top->pc, color,inst_val);
  
  trap_triggered = true;    // 标记已触发
  Verilated::gotFinish(true); 
}

static void single_cycle() {
  if (Verilated::gotFinish()) return;

  // Phase 1: Falling edge
  top->clk = 0;
  top->eval();
  tfp->dump(main_time++);

  // 提前退出检查点
  if (Verilated::gotFinish()) {
    tfp->close(); // 确保波形关闭
    return;
  }

  // Phase 2: Rising edge
  top->clk = 1;
  top->eval();
  tfp->dump(main_time++);

  // 更新指令存储器（仅在未触发时）
  if (!trap_triggered) {
    top->inst = pmem_read(top->pc);
  }
}

static void reset(int cycles = 2) {
  top->rst = 1;
  while (cycles-- > 0) single_cycle();
  top->rst = 0;
  assert((top->pc & 0x3) == 0);
}

int main() {
  Verilated::traceEverOn(true);
  top->trace(tfp, 99);
  tfp->open("waveform.fst");

  reset();

  while (!Verilated::gotFinish()) {
    single_cycle();
    if (main_time > 5000) {
      printf("\033[1;33mTimeout!\033[0m\n");
      break;
    }
  }

  // 确保资源释放
  tfp->close();
  delete top;
  delete tfp;
  printf("Simulation completed.\n");
  return 0;
}