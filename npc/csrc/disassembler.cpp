#include "../include/common.h"
#include "../include/debug.h"
#include <string.h>
#include <stdio.h>

#ifdef CONFIG_ITRACE

// RISC-V寄存器ABI名称
static const char* abi_reg_names[32] = {
  "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0/fp", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

// 初始化反汇编引擎
void init_disasm() {
  Log("RISC-V反汇编引擎初始化成功");
}

// 关闭反汇编引擎
void close_disasm() {
  // 无需操作
}

// 通过指令类型解析寄存器名称
static inline const char* reg_name(int reg) {
  if (reg >= 0 && reg < 32) {
    return abi_reg_names[reg];
  } else {
    return "??";
  }
}

// RISC-V反汇编函数
// addr: 指令的地址
// code: 指令的二进制编码
// 返回: 格式化后的汇编指令字符串
char* disasm_instr(uint64_t addr, uint32_t code) {
  static char disasm_buf[128];
  
  uint32_t opcode = code & 0x7f;
  uint32_t rd = (code >> 7) & 0x1f;
  uint32_t rs1 = (code >> 15) & 0x1f;
  uint32_t rs2 = (code >> 20) & 0x1f;
  uint32_t funct3 = (code >> 12) & 0x7;
  uint32_t funct7 = (code >> 25) & 0x7f;
  
  // I型立即数
  int32_t imm_i = ((int32_t)code) >> 20;
  // S型立即数
  int32_t imm_s = (((int32_t)code >> 25) << 5) | ((code >> 7) & 0x1f);
  // B型立即数（分支）
  int32_t imm_b = ((((int32_t)code >> 31) << 12) | 
                  ((code & 0x80) << 4) | 
                  ((code >> 25 & 0x3f) << 5) |
                  ((code >> 7 & 0x1e)));
  // U型立即数
  int32_t imm_u = (int32_t)(code & 0xfffff000);
  // J型立即数（跳转）
  int32_t imm_j = ((((int32_t)code >> 31) << 20) | 
                  ((code & 0xff000)) | 
                  ((code >> 20) & 0x1) << 11 | 
                  ((code >> 21) & 0x3ff) << 1);
  
  // 默认为unknown指令
  strcpy(disasm_buf, "unknown");
  
  switch (opcode) {
    // LUI: rd = imm << 12
    case 0x37: 
      snprintf(disasm_buf, sizeof(disasm_buf), "lui %s, 0x%x", 
              reg_name(rd), (code & 0xfffff000) >> 12);
      break;
      
    // AUIPC: rd = pc + (imm << 12)
    case 0x17: 
      snprintf(disasm_buf, sizeof(disasm_buf), "auipc %s, 0x%x", 
              reg_name(rd), (code & 0xfffff000) >> 12);
      break;
      
    // JAL: rd = pc+4; pc += imm
    case 0x6f: 
      snprintf(disasm_buf, sizeof(disasm_buf), "jal %s, 0x%x", 
              reg_name(rd), (int32_t)addr + imm_j);
      break;
      
    // JALR: rd = pc+4; pc = rs1 + imm
    case 0x67: 
      snprintf(disasm_buf, sizeof(disasm_buf), "jalr %s, %s, %d", 
              reg_name(rd), reg_name(rs1), imm_i);
      break;
      
    // 分支指令
    case 0x63: 
      switch (funct3) {
        case 0x0: snprintf(disasm_buf, sizeof(disasm_buf), "beq %s, %s, 0x%x", 
                          reg_name(rs1), reg_name(rs2), (int32_t)addr + imm_b); break;
        case 0x1: snprintf(disasm_buf, sizeof(disasm_buf), "bne %s, %s, 0x%x", 
                          reg_name(rs1), reg_name(rs2), (int32_t)addr + imm_b); break;
        case 0x4: snprintf(disasm_buf, sizeof(disasm_buf), "blt %s, %s, 0x%x", 
                          reg_name(rs1), reg_name(rs2), (int32_t)addr + imm_b); break;
        case 0x5: snprintf(disasm_buf, sizeof(disasm_buf), "bge %s, %s, 0x%x", 
                          reg_name(rs1), reg_name(rs2), (int32_t)addr + imm_b); break;
        case 0x6: snprintf(disasm_buf, sizeof(disasm_buf), "bltu %s, %s, 0x%x", 
                          reg_name(rs1), reg_name(rs2), (int32_t)addr + imm_b); break;
        case 0x7: snprintf(disasm_buf, sizeof(disasm_buf), "bgeu %s, %s, 0x%x", 
                          reg_name(rs1), reg_name(rs2), (int32_t)addr + imm_b); break;
      }
      break;
      
    // 加载指令
    case 0x03: 
      switch (funct3) {
        case 0x0: snprintf(disasm_buf, sizeof(disasm_buf), "lb %s, %d(%s)", 
                          reg_name(rd), imm_i, reg_name(rs1)); break;
        case 0x1: snprintf(disasm_buf, sizeof(disasm_buf), "lh %s, %d(%s)", 
                          reg_name(rd), imm_i, reg_name(rs1)); break;
        case 0x2: snprintf(disasm_buf, sizeof(disasm_buf), "lw %s, %d(%s)", 
                          reg_name(rd), imm_i, reg_name(rs1)); break;
        case 0x4: snprintf(disasm_buf, sizeof(disasm_buf), "lbu %s, %d(%s)", 
                          reg_name(rd), imm_i, reg_name(rs1)); break;
        case 0x5: snprintf(disasm_buf, sizeof(disasm_buf), "lhu %s, %d(%s)", 
                          reg_name(rd), imm_i, reg_name(rs1)); break;
      }
      break;
      
    // 存储指令
    case 0x23: 
      switch (funct3) {
        case 0x0: snprintf(disasm_buf, sizeof(disasm_buf), "sb %s, %d(%s)", 
                          reg_name(rs2), imm_s, reg_name(rs1)); break;
        case 0x1: snprintf(disasm_buf, sizeof(disasm_buf), "sh %s, %d(%s)", 
                          reg_name(rs2), imm_s, reg_name(rs1)); break;
        case 0x2: snprintf(disasm_buf, sizeof(disasm_buf), "sw %s, %d(%s)", 
                          reg_name(rs2), imm_s, reg_name(rs1)); break;
      }
      break;
      
    // I型指令
    case 0x13: 
      switch (funct3) {
        case 0x0: snprintf(disasm_buf, sizeof(disasm_buf), "addi %s, %s, %d", 
                          reg_name(rd), reg_name(rs1), imm_i); break;
        case 0x2: snprintf(disasm_buf, sizeof(disasm_buf), "slti %s, %s, %d", 
                          reg_name(rd), reg_name(rs1), imm_i); break;
        case 0x3: snprintf(disasm_buf, sizeof(disasm_buf), "sltiu %s, %s, %d", 
                          reg_name(rd), reg_name(rs1), imm_i); break;
        case 0x4: snprintf(disasm_buf, sizeof(disasm_buf), "xori %s, %s, %d", 
                          reg_name(rd), reg_name(rs1), imm_i); break;
        case 0x6: snprintf(disasm_buf, sizeof(disasm_buf), "ori %s, %s, %d", 
                          reg_name(rd), reg_name(rs1), imm_i); break;
        case 0x7: snprintf(disasm_buf, sizeof(disasm_buf), "andi %s, %s, %d", 
                          reg_name(rd), reg_name(rs1), imm_i); break;
        case 0x1: snprintf(disasm_buf, sizeof(disasm_buf), "slli %s, %s, %d", 
                          reg_name(rd), reg_name(rs1), (code >> 20) & 0x1f); break;
        case 0x5: 
          // 检查第30位(funct7[5])是否为1来区分srli和srai
          if (((code >> 30) & 0x1) == 0) {
            snprintf(disasm_buf, sizeof(disasm_buf), "srli %s, %s, %d", 
                    reg_name(rd), reg_name(rs1), (code >> 20) & 0x1f);
          } else {
            snprintf(disasm_buf, sizeof(disasm_buf), "srai %s, %s, %d", 
                    reg_name(rd), reg_name(rs1), (code >> 20) & 0x1f);
          }
          break;
      }
      break;
      
    // R型指令
    case 0x33:
      if (funct7 == 0x00) {
        switch (funct3) {
          case 0x0: snprintf(disasm_buf, sizeof(disasm_buf), "add %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x1: snprintf(disasm_buf, sizeof(disasm_buf), "sll %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x2: snprintf(disasm_buf, sizeof(disasm_buf), "slt %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x3: snprintf(disasm_buf, sizeof(disasm_buf), "sltu %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x4: snprintf(disasm_buf, sizeof(disasm_buf), "xor %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x5: snprintf(disasm_buf, sizeof(disasm_buf), "srl %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x6: snprintf(disasm_buf, sizeof(disasm_buf), "or %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x7: snprintf(disasm_buf, sizeof(disasm_buf), "and %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
        }
      } else if (funct7 == 0x01) {
        // M extension
        switch(funct3) {
          case 0x0: snprintf(disasm_buf, sizeof(disasm_buf), "mul %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x1: snprintf(disasm_buf, sizeof(disasm_buf), "mulh %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x2: snprintf(disasm_buf, sizeof(disasm_buf), "mulhsu %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x3: snprintf(disasm_buf, sizeof(disasm_buf), "mulhu %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x4: snprintf(disasm_buf, sizeof(disasm_buf), "div %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x5: snprintf(disasm_buf, sizeof(disasm_buf), "divu %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x6: snprintf(disasm_buf, sizeof(disasm_buf), "rem %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x7: snprintf(disasm_buf, sizeof(disasm_buf), "remu %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
        }
      } else if (funct7 == 0x20) {
        switch (funct3) {
          case 0x0: snprintf(disasm_buf, sizeof(disasm_buf), "sub %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
          case 0x5: snprintf(disasm_buf, sizeof(disasm_buf), "sra %s, %s, %s", 
                            reg_name(rd), reg_name(rs1), reg_name(rs2)); break;
        }
      }
      break;
      
    // 系统调用
    case 0x73:
      if (code == 0x00100073) {
        strcpy(disasm_buf, "ebreak");
      } else if (code == 0x00000073) {
        strcpy(disasm_buf, "ecall");
      } else {
        // CSR指令
        uint32_t csr = (code >> 20) & 0xfff;
        switch (funct3) {
          case 0x1: snprintf(disasm_buf, sizeof(disasm_buf), "csrrw %s, %03x, %s", 
                            reg_name(rd), csr, reg_name(rs1)); break;
          case 0x2: snprintf(disasm_buf, sizeof(disasm_buf), "csrrs %s, %03x, %s", 
                            reg_name(rd), csr, reg_name(rs1)); break;
          case 0x3: snprintf(disasm_buf, sizeof(disasm_buf), "csrrc %s, %03x, %s", 
                            reg_name(rd), csr, reg_name(rs1)); break;
          case 0x5: snprintf(disasm_buf, sizeof(disasm_buf), "csrrwi %s, %03x, %d", 
                            reg_name(rd), csr, rs1); break;
          case 0x6: snprintf(disasm_buf, sizeof(disasm_buf), "csrrsi %s, %03x, %d", 
                            reg_name(rd), csr, rs1); break;
          case 0x7: snprintf(disasm_buf, sizeof(disasm_buf), "csrrci %s, %03x, %d", 
                            reg_name(rd), csr, rs1); break;
        }
      }
      break;
  }
  
  return disasm_buf;
}

#endif // CONFIG_ITRACE
