#include "../include/paddr.h"
#include "Vrv32.h"
#include "Vrv32_rv32.h"


/********extern functions or variables********/
extern Vrv32 *top;
extern vluint64_t main_time;
/*********************************************/



uint8_t pmem[PMEM_SIZE] PG_ALIGN = {};
static const word_t img[] = {
  // 各种类型的RISC-V指令测试程序（主要是算术逻辑指令）
  
  // I型指令测试: addi, slti, xori, ori, andi, slli, srli, srai
  0x00500113,    // addi sp, zero, 5      ; sp = 5 (设置栈指针)
  0x06400593,    // addi a1, zero, 100    ; a1 = 100
  0x06458613,    // addi a2, a1, 100      ; a2 = a1 + 100 = 200
  0x0020a713,    // slti a4, a1, 2        ; a4 = (a1 < 2) ? 1 : 0 = 0
  0xff35c793,    // xori a5, a1, -13      ; a5 = a1 ^ (-13) 
  0x1ff7f813,    // andi a6, a5, 0x1ff    ; a6 = a5 & 0x1ff
  0x00159893,    // slli a7, a1, 1        ; a7 = a1 << 1 = 200
  0x0015d913,    // srli s2, a1, 1        ; s2 = a1 >> 1 = 50
  0x4015d993,    // srai s3, a1, 1        ; s3 = a1 >> 1 = 50 (算术)
  
  // R型指令测试: add, sub, sll, slt, sltu, xor, srl, sra, or, and
  0x00c58533,    // add a0, a1, a2        ; a0 = a1 + a2 = 300
  0x40c58a33,    // sub s4, a1, a2        ; s4 = a1 - a2 = -100
  0x00159ab3,    // sll s5, a1, a6        ; s5 = a1 << a6 
  0x00c5ab33,    // slt s6, a1, a2        ; s6 = (a1 < a2) ? 1 : 0 = 1
  0x00c5bbb3,    // sltu s7, a1, a2       ; s7 = (a1 <u a2) ? 1 : 0 = 1
  0x00c5cc33,    // xor s8, a1, a2        ; s8 = a1 ^ a2
  0x00c5dcb3,    // srl s9, a1, a2        ; s9 = a1 >> a2
  0x40c5dd33,    // sra s10, a1, a2       ; s10 = a1 >> a2 (算术)
  0x00c5edb3,    // or s11, a1, a2        ; s11 = a1 | a2
  0x00c5fe33,    // and t3, a1, a2        ; t3 = a1 & a2
  
  // U型指令测试: lui, auipc
  0x000010b7,    // lui ra, 1             ; ra = 1 << 12 = 4096
  0x00001137,    // lui sp, 1             ; sp = 1 << 12 = 4096
  0x00001097,    // auipc ra, 1           ; ra = pc + (1 << 12)
  
  // J型和B型指令测试 (小心使用，避免跳转到非法区域)
  0x00000513,    // addi a0, zero, 0      ; a0 = 0
  0x00100073,    // ebreak                ; 终止程序
  0xdeadbeef,    // some data             ; 一些数据
};



uint8_t* guest_to_host(paddr_t paddr) { return pmem + paddr - PMEM_BASE; }   //0x8000_0000 -> pmem[0]
paddr_t host_to_guest(uint8_t *haddr) { return haddr - pmem + PMEM_BASE; }


word_t host_read(void *addr, int len) 
{
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: return *(uint32_t *)addr;
    // case 8: return *(uint64_t *)addr;
    default: assert(0); return 0;
  }
}

static void host_write(void *addr, int len, word_t data) {
  switch (len) {
    case 1: *(uint8_t  *)addr = data; return;
    case 2: *(uint16_t *)addr = data; return;
    case 4: *(uint32_t *)addr = data; return;
    // case 8: *(uint64_t *)addr = data; return;
    default: assert(0);
  }
}

static inline bool in_pmem(paddr_t addr) {
  return (addr - PMEM_BASE < PMEM_SIZE);
}

static inline void out_of_bound(paddr_t addr) {
  panic("address = 0x%08x is out of bound of pmem [0x%08x, 0x%08x] at pc = 0x%08x  time = %ld", 
         addr, PMEM_LEFT, PMEM_RIGHT, top->rv32->pc, main_time);
}

word_t pmem_r(paddr_t addr, int len) 
{
#ifndef QUIET_MODE
  printf("paddr.cpp pmem_r\n");
#endif
  if(in_pmem(addr))   //check if within the bound
#ifdef CONFIG_MTRACE
  {
    word_t data = host_read(guest_to_host(addr), len);
    _Log(ANSI_FG_YELLOW "[mtrace]" ANSI_NONE " rd_mem  " ANSI_FG_YELLOW 
        "addr:" ANSI_NONE " 0x%08x  " ANSI_FG_YELLOW "data:" 
        ANSI_NONE " 0x%08x\n", addr, data);
    return data;
  }
#else
    return host_read(guest_to_host(addr), len);
#endif

  out_of_bound(addr);
  return 0;
}

void pmem_w(paddr_t addr, int len, word_t data) 
{
#ifndef QUIET_MODE
  printf("paddr.cpp pmem_w\n");
#endif
  if(in_pmem(addr))   //check if within the bound
  {
#ifdef CONFIG_MTRACE
    _Log(ANSI_FG_YELLOW "[mtrace]" ANSI_NONE " wr_mem  " ANSI_FG_YELLOW 
    "addr:" ANSI_NONE " 0x%08x  " ANSI_FG_YELLOW "data:" 
    ANSI_NONE " 0x%08x\n", addr, data);
#endif
    host_write(guest_to_host(addr), len, data);
    return;
  }  

  out_of_bound(addr);
}

void init_mem(void) 
{
  memset(pmem, 0, PMEM_SIZE);
  Log("physical memory area [0x%08x, 0x%08x]", PMEM_LEFT, PMEM_RIGHT);

  /* Load built-in image. */
  memcpy(guest_to_host(RESET_VECTOR), img, sizeof(img));
}