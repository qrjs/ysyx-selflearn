#ifndef __DISASSEMBLER_H__
#define __DISASSEMBLER_H__

#include "../include/common.h"

#ifdef CONFIG_ITRACE
// 初始化反汇编引擎
void init_disasm();

// 关闭反汇编引擎
void close_disasm();

// 反汇编单条指令
// addr: 指令的地址
// code: 指令的二进制编码
// 返回: 格式化后的汇编指令字符串
char* disasm_instr(uint64_t addr, uint32_t code);

#endif // CONFIG_ITRACE

#endif // __DISASSEMBLER_H__
