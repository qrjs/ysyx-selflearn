#include "../include/common.h"
#include "../include/utils.h"
#include "../include/debug.h"
#include "Vrv32.h"
#include "Vrv32_rv32.h"
#include "Vrv32_register_file.h"
#include <verilated.h>

extern Vrv32 *top;
extern NPCState npc_state;
extern vluint64_t main_time;
// 使用宏定义，删除重复声明
// extern void log_write(const char *fmt, ...);

#define start_time 3

// ALU单元名称
static const char *alu_names[16] = {
  "Unit_ALU", "Unit_MEM", "Unit_CU1", "Unit_CU2",
  "Unit_CU3", "Unit_CU4", "Unit_CU5", "Unit_CU6",
  "Unit_CU7", "Unit_CU8", "Unit_CU9", "Unit_CU10",
  "Unit_CU11","Unit_IE1", "Unit_IE2", "Unit_IE3"
};

// 替代原来的ebreak函数
extern "C" void ebreak(int station, int inst, char unit)
{
  if(Verilated::gotFinish())
    return;

  if(main_time >= start_time + 1 )  // 在开始时间后的操作才是有效的
  {
    // 保存中断状态
    // 使用与difftest.cpp中相同的宏定义
    #define top_regs top->rv32->register_file_inst->regs
    npc_state.halt_ret = top_regs[10]; //a0
    npc_state.halt_pc = top->rv32->pc;

#ifndef QUIET_MODE
    // 验证单元类型有效性
    if (!((unit == Unit_ALU) || (unit == Unit_CU1) || (unit == Unit_CU2) || (unit == Unit_CU3) || 
          (unit == Unit_CU4) || (unit == Unit_CU5) || (unit == Unit_CU6) || (unit == Unit_CU7) || 
          (unit == Unit_CU8) || (unit == Unit_CU9) || (unit == Unit_CU10)|| (unit == Unit_CU11)||
          (unit == Unit_MEM) || (unit == Unit_IE1) || (unit == Unit_IE2) || (unit == Unit_IE3))) {
      printf("\033[1;31m错误：无效的单元类型 %d\033[0m\n", unit);
    }
    
    // 仅打印非常规ebreak
    if (unit != Unit_CU9 || station == ABORT) { // Unit_CU9 通常是正常的系统调用ebreak，不打印错误
      printf("\033[1;31m⚠ Ebreak 在 %s 单元触发\033[0m\n", alu_names[unit]);
    }
#endif
    
    // 记录到日志
    // 修改为不使用log_write宏，因为这会导致编译错误
    extern FILE* log_fp;
    fprintf(log_fp, "EBREAK: unit=%s, pc=0x%08x, inst=0x%08x\n",
            alu_names[unit], top->rv32->pc, inst);
    fflush(log_fp);

    // 设置NPC状态
    switch(station)
    {
      case HIT_TRAP:
        npc_state.state = NPC_END;
        break;

      case ABORT:
      default:
        npc_state.state = NPC_ABORT;
        break;
    }

    Verilated::gotFinish(true);
  }
}
