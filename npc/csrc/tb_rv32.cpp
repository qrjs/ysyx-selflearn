#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vrv32.h"
#include "verilated_fst_c.h"
#include "Vrv32__Dpi.h"
#include "svdpi.h"
#include "../include/common.h"
#include "../include/utils.h"
#include "../include/debug.h"
#include "../include/disassembler.h"
#include "Vrv32_rv32.h"
#include "Vrv32_register_file.h"


VerilatedFstC* tfp = new VerilatedFstC(); // 导出vcd波形需要加此语句
Vrv32 *top = new Vrv32("top");
vluint64_t main_time = 0;  // initial 仿真时间


/********extern functions or variables********/
extern char *diff_so_file;
extern int  difftest_port;
extern long img_size;
extern NPCState npc_state;
extern void   init_monitor(int, char *[]);
extern void   sdb_mainloop();
extern int    is_exit_status_bad();
extern void   init_difftest(char *ref_so_file, long img_size, int port);
extern word_t pmem_r(paddr_t addr, int len); 
extern void   pmem_w(paddr_t addr, int len, word_t data);
// ebreak函数在ebreak_new.cpp中定义
extern int    pmem_read(int raddr);                            // mem.v
extern int    pmem_read_inst(int pc);
extern void   pmem_write(int waddr, int wdata, char wmask);    // mem.v
/*********************************************/

#define start_time 3

static const char *alu_names[16] = {
  "Unit_ALU", "Unit_MEM", "Unit_CU1", "Unit_CU2",
  "Unit_CU3", "Unit_CU4", "Unit_CU5", "Unit_CU6",
  "Unit_CU7", "Unit_CU8", "Unit_CU9", "Unit_CU10",
  "Unit_CU11","Unit_IE1", "Unit_IE2", "Unit_IE3"
};

// ebreak函数已经移动到ebreak_new.cpp

extern int pmem_read(int raddr)
{
  // 仅在调试模式下输出内存读取信息
#ifndef QUIET_MODE
  printf("内存读取: 地址=0x%x\n", raddr);
#endif
  static int data = 0xdeadbeaf;

  if(main_time >= start_time)
  {
    data = pmem_r(raddr, 4);
    return data; 
  } 
  else
    return 0xdeadbeaf;
}


void pmem_write(int waddr, int wdata, char wmask)
{
  if(top->clk == 0)
    return;

#ifndef QUIET_MODE
  printf("内存写入: 地址=0x%08x, 数据=0x%08x, 掩码=0x%02x\n", waddr, wdata, wmask);
#endif

  switch (wmask)
  {
    case WByte: pmem_w(waddr, 1, wdata);
                break;
    case WHalf: pmem_w(waddr, 2, wdata);
                break;
    case WWord: pmem_w(waddr, 4, wdata);
                break;
    default:    assert(0);
                break;
  }
}


void single_cycle(void) 
{
#ifndef QUIET_MODE
  printf("执行单个周期\n");
#endif
  if(!Verilated::gotFinish())
  { 
    top->clk = 1; top->eval(); tfp->dump(main_time);  main_time++; 
    top->clk = 0; top->eval(); tfp->dump(main_time);  main_time++; 
  }
}

static void reset(void)
{
#ifndef QUIET_MODE
  printf("\033[1;33m系统重置...\033[0m\n");
#endif
  top->rst = 0; single_cycle();
  top->rst = 1; single_cycle();
  top->rst = 0; 
#ifndef QUIET_MODE
  printf("\033[1;32m重置完成!\033[0m\n");
#endif
}

static void init_verilator(void)
{
  Verilated::traceEverOn(true); // 导出vcd波形需要加此语句

  top->trace(tfp, 0);
  tfp->open("waveform.fst"); // 打开fst

  reset();  // 复位
}

int main(int argc, char *argv[])
{
  /* Initialize the monitor. */
  init_monitor(argc, argv);

  /* Initialize the verilator. */
  init_verilator();

#ifdef CONFIG_ITRACE
  /* Initialize capstone disassembly engine. */
  init_disasm();
#endif

#ifdef CONFIG_DIFFTEST
  /* Initialize differential testing. */
  if (diff_so_file != NULL) {
    init_difftest(diff_so_file, img_size, difftest_port);
  }
#endif

  /* Receive commands from user. */
  sdb_mainloop();

  /* End the simulation */
  top->final();
  tfp->close();
  delete top;

#ifdef CONFIG_ITRACE
  /* Cleanup capstone disassembly engine. */
  close_disasm();
#endif

  return is_exit_status_bad();
}
