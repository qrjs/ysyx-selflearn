#include "../include/difftest.h"
#include <dlfcn.h>
#include "Vrv32.h"
#include "Vrv32_rv32.h"
#include "Vrv32_register_file.h"

/********extern functions or variables********/
extern Vrv32 *top;                  // 顶层Verilator模型实例
extern NPCState npc_state;          // NPC状态
extern uint8_t* guest_to_host(paddr_t paddr); // 客户内存地址转换为主机内存地址的函数
/*********************************************/

#ifdef CONFIG_DIFFTEST

// 获取Verilator模型中的寄存器文件
#define top_regs top->rv32->register_file_inst->regs

// DiffTest引用模型函数指针
void (*ref_difftest_memcpy)(paddr_t addr, void *buf, size_t n, bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
void (*ref_difftest_exec)(uint64_t n) = NULL;

// RISC-V寄存器名称数组，用于调试输出
const char *ref_regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};


/**
 * 初始化CPU状态结构体
 * 
 * 从Verilator模型中提取当前PC值和寄存器值
 * 用于DiffTest对比
 */
static void init_cpu_state(CPU_state *cpu)
{
    cpu->pc = top->rv32->pc;           // 获取当前PC值
    for(int i = 0; i < 32; i++)
        cpu->gpr[i] = top_regs[i];     // 获取所有通用寄存器的值
}

/**
 * 初始化DiffTest
 * 
 * 加载参考模型动态库并获取函数接口
 * 设置初始状态，使NPC与参考模型状态一致
 */
void init_difftest(char *ref_so_file, long img_size, int port) 
{
    CPU_state cpu;
    init_cpu_state(&cpu);              // 初始化CPU状态

    assert(ref_so_file != NULL);       // 确保参考模型路径非空

    void *handle;
    handle = dlopen(ref_so_file, RTLD_LAZY); // 加载参考模型动态库
    assert(handle);

    // 获取参考模型的内存复制函数
    // 获取参考模型的内存复制函数
    ref_difftest_memcpy = (void (*)(uint32_t, void*, size_t, bool))dlsym(handle, "difftest_memcpy");
    assert(ref_difftest_memcpy);

    // 获取参考模型的寄存器复制函数
    ref_difftest_regcpy = (void (*)(void*, bool))dlsym(handle, "difftest_regcpy");
    assert(ref_difftest_regcpy);

    // 获取参考模型的执行函数
    ref_difftest_exec = (void (*)(uint64_t))dlsym(handle, "difftest_exec");
    assert(ref_difftest_exec);

    // 中断相关功能暂未使用
    // ref_difftest_raise_intr = dlsym(handle, "difftest_raise_intr");
    // assert(ref_difftest_raise_intr);

    // 获取参考模型的初始化函数
    void (*ref_difftest_init)(int) = (void (*)(int))dlsym(handle, "difftest_init");
    assert(ref_difftest_init);

    Log("The result of every instruction will be compared with %s. "
        "This will help you a lot for debugging, but also significantly reduce the performance. ", ref_so_file);

    // 初始化参考模型
    ref_difftest_init(port);
    
    // 将程序镜像复制到参考模型中
    ref_difftest_memcpy(RESET_VECTOR, guest_to_host(RESET_VECTOR), img_size, DIFFTEST_TO_REF);
    
    // 将NPC的寄存器状态复制到参考模型中
    ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
}

/**
 * 检查NPC与参考模型的寄存器是否一致
 * 
 * 比较PC和所有通用寄存器的值
 * 如果不一致，打印详细信息并返回失败
 */
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) 
{
    bool success = true;

    //检查PC值
    if(ref_r->pc != pc)
    {
        _Log(ANSI_FG_YELLOW "[difftest]" ANSI_NONE   ANSI_FG_RED "pc" 
             ANSI_NONE "  dut:0x%08x   ref:0x%08x\n", pc, ref_r->pc);
        success = false;
    }
    
    //检查通用寄存器
    for(int i = 0; i < 32; i++)
        if(top_regs[i] != ref_r->gpr[i])
        {
            _Log(ANSI_FG_YELLOW "[difftest]" ANSI_NONE   ANSI_FG_RED "%s" 
                 ANSI_NONE "  dut:0x%08x   ref:0x%08x\n", ref_regs[i], top_regs[i], ref_r->gpr[i]);
            success = false;
        }
    
    // 打印验证结果
    if(success){
    	Log(ANSI_FG_GREEN  "[difftest pass] \n" );
    }else{
    	Log(ANSI_FG_RED  "[difftest nopass] \n" );
    }
    return success;
}

/**
 * 检查寄存器并处理不一致的情况
 * 
 * 如果DiffTest失败，设置NPC状态为ABORT并记录当前PC
 */
static void checkregs(CPU_state *ref, vaddr_t pc, vaddr_t npc) 
{
    if (!isa_difftest_checkregs(ref, npc)) 
    {
        npc_state.state = NPC_ABORT;      // 设置NPC状态为终止
        npc_state.halt_pc = pc;           // 记录终止时的PC值
        Log("Differential test %s at pc = 0x%08x." , (ANSI_FMT("fails", ANSI_FG_RED)), npc_state.halt_pc);
    }
}

/**
 * 执行一步DiffTest比较
 * 
 * 让参考模型执行一条指令，然后比较结果
 * 
 * @param pc  当前指令的PC值
 * @param npc 下一条指令的PC值
 */
void difftest_step(vaddr_t pc, vaddr_t npc) 
{
    CPU_state ref_r;

    // 让参考模型执行一条指令
    ref_difftest_exec(1);
    
    // 从参考模型获取寄存器状态
    ref_difftest_regcpy(&ref_r, DIFFTEST_TO_DUT);

    // 检查NPC与参考模型的寄存器状态是否一致
    checkregs(&ref_r, pc, npc);
}


#else
// 如果未启用DiffTest，提供空实现
void init_difftest(char *ref_so_file, long img_size, int port) { }
#endif