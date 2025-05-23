#include "../include/common.h"
#include "../include/utils.h"
#include "../include/debug.h"
#include "../include/macro.h"
#include "Vrv32.h"
#include "Vrv32_rv32.h"
#include "Vrv32_register_file.h"
#include <time.h> // 添加time.h头文件

/********extern functions or variables********/
extern void single_cycle(void); 
extern NPCState npc_state;
extern Vrv32 *top;

#ifdef CONFIG_FTRACE 
extern void RET_Log(uint32_t pc, uint32_t npc);
extern void J_Log(uint32_t pc, uint32_t npc);
#define OPCODE(inst)  ((inst) & 0x7f)
#endif

#ifdef CONFIG_IRINGBUF 
extern void append_iringbuf(char *s);
extern void display_iringbuf(void);
#endif

#ifdef CONFIG_DIFFTEST 
extern void difftest_step(vaddr_t pc, vaddr_t npc);
#endif
/*********************************************/


#define MAX_INST_TO_PRINT 20
static uint64_t g_nr_guest_inst = 0;
static bool g_print_step = false;
IFDEF(CONFIG_ITRACE, char logbuf[128]);


static struct {
  word_t pc;
  word_t npc;
  word_t inst;
  word_t ninst;
} PCSet = {0, 0, 0, 0};


static void statistic() {
    Log("total guest instructions = %lu", g_nr_guest_inst);
}

// 美化输出的辅助函数
// force_display: 如果设为true，即使在QUIET_MODE下也会显示执行信息
static void print_execution_info(uint32_t pc, uint32_t inst, bool force_display = false) {
    // 在QUIET_MODE下只有force_display为true时显示，在非QUIET_MODE下总是显示
    if (!force_display && QUIET_MODE) {
        return;
    }
    
    static int step_count = 0;
    step_count++; // 增加指令计数器
    
    // 显示执行指令的序号和时间信息
    time_t now;
    struct tm *timeinfo;
    char timestr[9];
    time(&now);
    timeinfo = localtime(&now);
    strftime(timestr, 9, "%H:%M:%S", timeinfo);
    
    printf("\n\033[1;90m-------------------------------------------------------\033[0m\n");
    printf("\033[1;45;37m 指令 #%-6d (%s) \033[0m\n", step_count, timestr);
    
    // 获取指令类型和字段
    uint32_t opcode = inst & 0x7f;
    uint32_t funct3 = (inst >> 12) & 0x7;
    uint32_t funct7 = (inst >> 25) & 0x7f;
    uint32_t rd = (inst >> 7) & 0x1f;
    uint32_t rs1 = (inst >> 15) & 0x1f;
    uint32_t rs2 = (inst >> 20) & 0x1f;
    uint32_t imm_i = ((int32_t)inst) >> 20; // 符号扩展
    uint32_t imm_s = (((int32_t)inst) >> 25 << 5) | ((inst >> 7) & 0x1f);
    uint32_t imm_b = (((int32_t)inst >> 31) << 12) | ((inst & 0x80) << 4) | ((inst >> 25 & 0x3f) << 5) | ((inst >> 8 & 0xf) << 1);
    uint32_t imm_u = inst & 0xfffff000;
    uint32_t imm_j = (((int32_t)inst >> 31) << 20) | ((inst & 0xff000) << 0) | ((inst >> 20 & 0x1) << 11) | ((inst >> 21 & 0x3ff) << 1);
    
    // 类似于截图中的指令格式的构建
    char asm_str[128] = "";
    char instr_name[32] = "unknown";
    char operands[64] = "";
    
    // 根据指令类型解析指令
    switch (opcode) {
        case 0x03: // Load 指令
            switch(funct3) {
                case 0: 
                    strcpy(instr_name, "lb"); 
                    sprintf(operands, "x%d, %d(x%d)", rd, (int32_t)imm_i, rs1);
                    break;
                case 1: 
                    strcpy(instr_name, "lh"); 
                    sprintf(operands, "x%d, %d(x%d)", rd, (int32_t)imm_i, rs1);
                    break;
                case 2: 
                    strcpy(instr_name, "lw"); 
                    sprintf(operands, "x%d, %d(x%d)", rd, (int32_t)imm_i, rs1);
                    break;
                case 4: 
                    strcpy(instr_name, "lbu"); 
                    sprintf(operands, "x%d, %d(x%d)", rd, (int32_t)imm_i, rs1);
                    break;
                case 5: 
                    strcpy(instr_name, "lhu"); 
                    sprintf(operands, "x%d, %d(x%d)", rd, (int32_t)imm_i, rs1);
                    break;
            }
            break;
        case 0x23: // Store 指令
            switch(funct3) {
                case 0: 
                    strcpy(instr_name, "sb"); 
                    sprintf(operands, "x%d, %d(x%d)", rs2, (int32_t)imm_s, rs1);
                    break;
                case 1: 
                    strcpy(instr_name, "sh"); 
                    sprintf(operands, "x%d, %d(x%d)", rs2, (int32_t)imm_s, rs1);
                    break;
                case 2: 
                    strcpy(instr_name, "sw"); 
                    sprintf(operands, "x%d, %d(x%d)", rs2, (int32_t)imm_s, rs1);
                    break;
            }
            break;
        case 0x63: // Branch 指令
            switch(funct3) {
                case 0: 
                    strcpy(instr_name, "beq"); 
                    sprintf(operands, "x%d, x%d, 0x%x", rs1, rs2, pc + (int32_t)imm_b);
                    break;
                case 1: 
                    strcpy(instr_name, "bne"); 
                    sprintf(operands, "x%d, x%d, 0x%x", rs1, rs2, pc + (int32_t)imm_b);
                    break;
                case 4: 
                    strcpy(instr_name, "blt"); 
                    sprintf(operands, "x%d, x%d, 0x%x", rs1, rs2, pc + (int32_t)imm_b);
                    break;
                case 5: 
                    strcpy(instr_name, "bge"); 
                    sprintf(operands, "x%d, x%d, 0x%x", rs1, rs2, pc + (int32_t)imm_b);
                    break;
                case 6: 
                    strcpy(instr_name, "bltu"); 
                    sprintf(operands, "x%d, x%d, 0x%x", rs1, rs2, pc + (int32_t)imm_b);
                    break;
                case 7: 
                    strcpy(instr_name, "bgeu"); 
                    sprintf(operands, "x%d, x%d, 0x%x", rs1, rs2, pc + (int32_t)imm_b);
                    break;
            }
            break;
        case 0x13: // I-type 立即数指令
            switch(funct3) {
                case 0: 
                    strcpy(instr_name, "addi"); 
                    sprintf(operands, "x%d, x%d, %d", rd, rs1, (int32_t)imm_i);
                    break;
                case 1: 
                    strcpy(instr_name, "slli"); 
                    sprintf(operands, "x%d, x%d, %d", rd, rs1, imm_i & 0x1f);
                    break;
                case 2: 
                    strcpy(instr_name, "slti"); 
                    sprintf(operands, "x%d, x%d, %d", rd, rs1, (int32_t)imm_i);
                    break;
                case 3: 
                    strcpy(instr_name, "sltiu"); 
                    sprintf(operands, "x%d, x%d, %d", rd, rs1, imm_i);
                    break;
                case 4: 
                    strcpy(instr_name, "xori"); 
                    sprintf(operands, "x%d, x%d, %d", rd, rs1, (int32_t)imm_i);
                    break;
                case 5: 
                    if(funct7 == 0) {
                        strcpy(instr_name, "srli"); 
                        sprintf(operands, "x%d, x%d, %d", rd, rs1, imm_i & 0x1f);
                    } else {
                        strcpy(instr_name, "srai"); 
                        sprintf(operands, "x%d, x%d, %d", rd, rs1, imm_i & 0x1f);
                    }
                    break;
                case 6: 
                    strcpy(instr_name, "ori"); 
                    sprintf(operands, "x%d, x%d, %d", rd, rs1, (int32_t)imm_i);
                    break;
                case 7: 
                    strcpy(instr_name, "andi"); 
                    sprintf(operands, "x%d, x%d, %d", rd, rs1, (int32_t)imm_i);
                    break;
            }
            break;
        case 0x33: // R-type 寄存器运算指令
            if (funct7 == 0) {
                switch(funct3) {
                    case 0: 
                        strcpy(instr_name, "add"); 
                        sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
                        break;
                    case 1: 
                        strcpy(instr_name, "sll"); 
                        sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
                        break;
                    case 2: 
                        strcpy(instr_name, "slt"); 
                        sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
                        break;
                    case 3: 
                        strcpy(instr_name, "sltu"); 
                        sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
                        break;
                    case 4: 
                        strcpy(instr_name, "xor"); 
                        sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
                        break;
                    case 5: 
                        strcpy(instr_name, "srl"); 
                        sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
                        break;
                    case 6: 
                        strcpy(instr_name, "or"); 
                        sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
                        break;
                    case 7: 
                        strcpy(instr_name, "and"); 
                        sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
                        break;
                }
            } else if (funct7 == 0x20) {
                switch(funct3) {
                    case 0: 
                        strcpy(instr_name, "sub"); 
                        sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
                        break;
                    case 5: 
                        strcpy(instr_name, "sra"); 
                        sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
                        break;
                }
            }
            break;
        case 0x37: // LUI
            strcpy(instr_name, "lui"); 
            sprintf(operands, "x%d, 0x%x", rd, imm_u >> 12);
            break;
        case 0x17: // AUIPC
            strcpy(instr_name, "auipc"); 
            sprintf(operands, "x%d, 0x%x", rd, imm_u >> 12);
            break;
        case 0x6f: // JAL
            strcpy(instr_name, "jal"); 
            sprintf(operands, "x%d, 0x%x", rd, pc + (int32_t)imm_j);
            break;
        case 0x67: // JALR
            strcpy(instr_name, "jalr"); 
            sprintf(operands, "x%d, x%d, %d", rd, rs1, (int32_t)imm_i);
            break;
        case 0x73: // EBREAK
            strcpy(instr_name, "ebreak");
            break;
    }
    
    // 格式化完整的汇编字符串
    if (operands[0] != '\0') {
        sprintf(asm_str, "%s %s", instr_name, operands);
    } else {
        strcpy(asm_str, instr_name);
    }
    
    // 使用简洁的格式输出指令信息
    bool is_pc_changed = (pc + 4) != PCSet.npc; // 检查PC是否发生非顺序变化
    
    printf("\n\033[1;44;37m 指令执行信息 \033[0m\n");
    
    // 为不同指令类型添加图标
    char instr_type_icon[10] = "📋"; // 默认图标
    if ((opcode == 0x03) || (opcode == 0x23)) strcpy(instr_type_icon, "💾"); // 内存操作
    else if (opcode == 0x63) strcpy(instr_type_icon, "🔀"); // 分支
    else if (opcode == 0x6f || opcode == 0x67) strcpy(instr_type_icon, "⤴️ "); // 跳转
    else if (opcode == 0x33) strcpy(instr_type_icon, "🧮"); // ALU操作
    else if (opcode == 0x73) strcpy(instr_type_icon, "⚠️ "); // 系统调用
    
    // 显示PC和指令编码
    printf("\033[1;36mPC:\033[0m \033[1;33m0x%08x\033[0m → \033[1;33m0x%08x\033[0m %-15s\n", 
           pc, PCSet.npc, is_pc_changed ? "\033[1;31m[跳转]\033[0m" : "");
    
    printf("\033[1;36m指令:\033[0m \033[1;33m0x%08x\033[0m %s \033[1;32m%s\033[0m\n", 
           inst, instr_type_icon, asm_str);
    
    // 对寄存器进行映射，使其显示更友好
    const char *reg_names[] = {
        "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
        "s0/fp", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
        "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
        "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
    };
    
    // 显示指令使用的寄存器，采用简洁的格式显示
    printf("\033[1;35m寄存器值:\033[0m\n");
    
    // 预先计算分支是否跳转
    bool taken = (PCSet.npc != pc + 4);
    
    switch (opcode) {
        case 0x03: // Load 指令
        case 0x13: // I-type
        case 0x67: // JALR
            printf("  \033[1;36mrs1\033[0m (\033[1;36m%-8s\033[0m, x%-2d): \033[1;32m0x%08x\033[0m\n", 
                   reg_names[rs1], rs1, top->rv32->register_file_inst->regs[rs1]);
            printf("  \033[1;36mrd \033[0m (\033[1;36m%-8s\033[0m, x%-2d): \033[1;32m0x%08x\033[0m\n", 
                   reg_names[rd], rd, top->rv32->register_file_inst->regs[rd]);
            break;
            
        case 0x33: // R-type
            printf("  \033[1;36mrs1\033[0m (\033[1;36m%-8s\033[0m, x%-2d): \033[1;32m0x%08x\033[0m\n", 
                   reg_names[rs1], rs1, top->rv32->register_file_inst->regs[rs1]);
            printf("  \033[1;36mrs2\033[0m (\033[1;36m%-8s\033[0m, x%-2d): \033[1;32m0x%08x\033[0m\n", 
                   reg_names[rs2], rs2, top->rv32->register_file_inst->regs[rs2]);
            printf("  \033[1;36mrd \033[0m (\033[1;36m%-8s\033[0m, x%-2d): \033[1;32m0x%08x\033[0m\n", 
                   reg_names[rd], rd, top->rv32->register_file_inst->regs[rd]);
            break;
            
        case 0x23: // Store 指令
            printf("  \033[1;36mrs1\033[0m (\033[1;36m%-8s\033[0m, x%-2d): \033[1;32m0x%08x\033[0m\n", 
                   reg_names[rs1], rs1, top->rv32->register_file_inst->regs[rs1]);
            printf("  \033[1;36mrs2\033[0m (\033[1;36m%-8s\033[0m, x%-2d): \033[1;32m0x%08x\033[0m\n", 
                   reg_names[rs2], rs2, top->rv32->register_file_inst->regs[rs2]);
            break;
            
        case 0x63: // Branch 指令
            printf("  \033[1;36mrs1\033[0m (\033[1;36m%-8s\033[0m, x%-2d): \033[1;32m0x%08x\033[0m\n", 
                   reg_names[rs1], rs1, top->rv32->register_file_inst->regs[rs1]);
            printf("  \033[1;36mrs2\033[0m (\033[1;36m%-8s\033[0m, x%-2d): \033[1;32m0x%08x\033[0m\n", 
                   reg_names[rs2], rs2, top->rv32->register_file_inst->regs[rs2]);
            printf("  \033[1;33m分支状态: %s\033[0m\n", taken ? "✓ 跳转" : "✗ 不跳转");
            break;
            
        case 0x37: // LUI
        case 0x17: // AUIPC
        case 0x6f: // JAL
            printf("  \033[1;36mrd \033[0m (\033[1;36m%-8s\033[0m, x%-2d): \033[1;32m0x%08x\033[0m\n", 
                   reg_names[rd], rd, top->rv32->register_file_inst->regs[rd]);
            break;
    }
    
    // 如果是ebreak指令，显示系统调用信息
    if (opcode == 0x73) { // ebreak
        printf("\n\033[1;42;30m                系统调用信息                 \033[0m\n");
        printf("  \033[1;32m✓ EBREAK系统调用已触发\033[0m\n");
        printf("  \033[1;33m- 系统调用号: %d\033[0m\n", top->rv32->register_file_inst->regs[17]); // a7寄存器
        printf("  \033[1;33m- 返回值位置: x10(a0)\033[0m\n");
    }
    
    // 简化的分隔线
    printf("\n\033[1;90m");
    printf("-------------------------------------------------------\033[0m\n");
}

static void execute_once(bool force_display = false) 
{
    // 收集当前PC和指令
    PCSet.pc = top->rv32->pc;  PCSet.inst = top->rv32->inst;
    
    // 先执行单个周期，让CPU计算出下一个PC值
    single_cycle(); 
    
    // 收集下一条PC和指令
    PCSet.npc = top->rv32->pc;  PCSet.ninst = top->rv32->inst;
    
    // 显示漂亮的执行信息（带有强制显示标志）
    print_execution_info(PCSet.pc, PCSet.inst, force_display);
    
#ifdef CONFIG_ITRACE
    char *p = logbuf;
    
    // 获取指令的简单反汇编
    uint32_t inst = PCSet.inst;
    uint32_t opcode = inst & 0x7f;
    uint32_t funct3 = (inst >> 12) & 0x7;
    uint32_t funct7 = (inst >> 25) & 0x7f;
    uint32_t rd = (inst >> 7) & 0x1f;
    uint32_t rs1 = (inst >> 15) & 0x1f;
    uint32_t rs2 = (inst >> 20) & 0x1f;
    uint32_t imm_i = ((int32_t)inst) >> 20;
    uint32_t imm_s = (((int32_t)inst) >> 25 << 5) | ((inst >> 7) & 0x1f);
    uint32_t imm_b = (((int32_t)inst >> 31) << 12) | ((inst & 0x80) << 4) | ((inst >> 25 & 0x3f) << 5) | ((inst >> 8 & 0xf) << 1);
    uint32_t imm_u = inst & 0xfffff000;
    uint32_t imm_j = (((int32_t)inst >> 31) << 20) | ((inst & 0xff000) << 0) | ((inst >> 20 & 0x1) << 11) | ((inst >> 21 & 0x3ff) << 1);
    
    char asm_str[64] = "";
    char instr_name[16] = "unknown";
    char operands[48] = "";
    
    // 使用和print_execution_info相同的逻辑进行反汇编
    switch (opcode) {
        case 0x03: // Load 指令
            switch(funct3) {
                case 0: strcpy(instr_name, "lb"); break;
                case 1: strcpy(instr_name, "lh"); break;
                case 2: strcpy(instr_name, "lw"); break;
                case 4: strcpy(instr_name, "lbu"); break;
                case 5: strcpy(instr_name, "lhu"); break;
            }
            sprintf(operands, "x%d, %d(x%d)", rd, (int32_t)imm_i, rs1);
            break;
        case 0x23: // Store 指令
            switch(funct3) {
                case 0: strcpy(instr_name, "sb"); break;
                case 1: strcpy(instr_name, "sh"); break;
                case 2: strcpy(instr_name, "sw"); break;
            }
            sprintf(operands, "x%d, %d(x%d)", rs2, (int32_t)imm_s, rs1);
            break;
        case 0x63: // Branch 指令
            switch(funct3) {
                case 0: strcpy(instr_name, "beq"); break;
                case 1: strcpy(instr_name, "bne"); break;
                case 4: strcpy(instr_name, "blt"); break;
                case 5: strcpy(instr_name, "bge"); break;
                case 6: strcpy(instr_name, "bltu"); break;
                case 7: strcpy(instr_name, "bgeu"); break;
            }
            sprintf(operands, "x%d, x%d, 0x%x", rs1, rs2, PCSet.pc + (int32_t)imm_b);
            break;
        case 0x13: // I-type
            switch(funct3) {
                case 0: strcpy(instr_name, "addi"); break;
                case 1: strcpy(instr_name, "slli"); break;
                case 2: strcpy(instr_name, "slti"); break;
                case 3: strcpy(instr_name, "sltiu"); break;
                case 4: strcpy(instr_name, "xori"); break;
                case 5: strcpy(instr_name, (funct7 == 0) ? "srli" : "srai"); break;
                case 6: strcpy(instr_name, "ori"); break;
                case 7: strcpy(instr_name, "andi"); break;
            }
            // 对于移位指令，只使用低5位作为移位量
            if (funct3 == 1 || funct3 == 5) {
                sprintf(operands, "x%d, x%d, %d", rd, rs1, imm_i & 0x1f);
            } else {
                sprintf(operands, "x%d, x%d, %d", rd, rs1, (int32_t)imm_i);
            }
            break;
        case 0x33: // R-type
            if (funct7 == 0) {
                switch(funct3) {
                    case 0: strcpy(instr_name, "add"); break;
                    case 1: strcpy(instr_name, "sll"); break;
                    case 2: strcpy(instr_name, "slt"); break;
                    case 3: strcpy(instr_name, "sltu"); break;
                    case 4: strcpy(instr_name, "xor"); break;
                    case 5: strcpy(instr_name, "srl"); break;
                    case 6: strcpy(instr_name, "or"); break;
                    case 7: strcpy(instr_name, "and"); break;
                }
            } else if (funct7 == 0x20) {
                switch(funct3) {
                    case 0: strcpy(instr_name, "sub"); break;
                    case 5: strcpy(instr_name, "sra"); break;
                }
            }
            sprintf(operands, "x%d, x%d, x%d", rd, rs1, rs2);
            break;
        case 0x37: // LUI
            strcpy(instr_name, "lui");
            sprintf(operands, "x%d, 0x%x", rd, imm_u >> 12);
            break;
        case 0x17: // AUIPC
            strcpy(instr_name, "auipc");
            sprintf(operands, "x%d, 0x%x", rd, imm_u >> 12);
            break;
        case 0x6f: // JAL
            strcpy(instr_name, "jal");
            sprintf(operands, "x%d, 0x%x", rd, PCSet.pc + (int32_t)imm_j);
            break;
        case 0x67: // JALR
            strcpy(instr_name, "jalr");
            sprintf(operands, "x%d, x%d, %d", rd, rs1, (int32_t)imm_i);
            break;
        case 0x73: // EBREAK
            strcpy(instr_name, "ebreak");
            break;
    }
    
    if (operands[0] != '\0') {
        sprintf(asm_str, "%s %s", instr_name, operands);
    } else {
        strcpy(asm_str, instr_name);
    }
    
    p += snprintf(p, sizeof(logbuf) - (p - logbuf), "0x%08x: 0x%08x %s", PCSet.pc, PCSet.inst, asm_str);
    *p = '\0';
#endif

#ifdef CONFIG_FTRACE
  if(PCSet.inst == 0x00008067)  //ret
    RET_Log(PCSet.pc, PCSet.npc);
  else if((OPCODE(PCSet.inst)==0b1100111) || (OPCODE(PCSet.inst)== 0b1101111))  //jalr or jal
    J_Log(PCSet.pc, PCSet.npc);
#endif

#ifdef CONFIG_IRINGBUF 
    append_iringbuf(logbuf);
#endif
}

static void trace_and_difftest() 
{
    // itrace - 将指令轨迹写入日志文件
    #ifdef CONFIG_ITRACE
        log_write("%s\n", logbuf);
    #endif
    
    // 在安静模式下不输出
    #ifndef QUIET_MODE
    // 仅当设置步进模式时才打印指令轨迹
    if(g_print_step) 
        IFDEF(CONFIG_ITRACE, printf("\033[1;90m历史记录: \033[0m\033[1;36m%s\033[0m\n", logbuf)); 
    #endif

    // difftest - 执行差分测试
    IFDEF(CONFIG_DIFFTEST, difftest_step(PCSet.pc, PCSet.npc));

}

static void execute(uint64_t n, bool force_display = false) 
{
    for (;n > 0; n --) 
    {    
        execute_once(force_display);
        g_nr_guest_inst ++;
        trace_and_difftest();
        if (npc_state.state != NPC_RUNNING) 
            break;
    }
}


// 这里之前有重复的print_execution_info函数定义，已删除

void cpu_exec(uint64_t n, bool force_display = false) 
{
    g_print_step = (n < MAX_INST_TO_PRINT);
    switch (npc_state.state) 
    {
        case NPC_END: case NPC_ABORT:
            printf("\033[1;33m程序执行已结束。要重启程序，请退出NPC并重新运行。\033[0m\n");
            return;
        default: npc_state.state = NPC_RUNNING;
    }   

    execute(n, force_display);

    switch (npc_state.state) 
    {
        case NPC_RUNNING: npc_state.state = NPC_STOP; break;

        case NPC_END: case NPC_ABORT:
#ifdef CONFIG_IRINGBUF 
            display_iringbuf();
#endif
            if (npc_state.state == NPC_ABORT) {
                printf("\033[1;31m✗ ABORT 在 pc = 0x%08x\033[0m\n", npc_state.halt_pc);
            } else if (npc_state.halt_ret == 0) {
                printf("\033[1;32m✓ 测试通过 (HIT GOOD TRAP) 在 pc = 0x%08x\033[0m\n", npc_state.halt_pc);
            } else {
                printf("\033[1;31m✗ 测试失败 (HIT BAD TRAP) 在 pc = 0x%08x\033[0m\n", npc_state.halt_pc);
            }
            // 将程序状态写入日志文件，以便Makefile能检测到
            if (npc_state.state == NPC_ABORT || (npc_state.state == NPC_END && npc_state.halt_ret != 0)) {
                FILE *fp = fopen("./test_status.txt", "w");
                if (fp) {
                    fprintf(fp, "FAIL\n");
                    fclose(fp);
                    exit(1); // 直接返回错误码
                }
            }
        case NPC_QUIT: statistic();
    }
}