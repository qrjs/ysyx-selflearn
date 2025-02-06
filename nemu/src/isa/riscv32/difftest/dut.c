/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"

#define CHECKDIFFPC(p) if (ref_r->p != cpu.p) { \
  printf("difftest fail at " #p ", expect %#x got %#x\n", ref_r->p, cpu.p); \
  error = 1; \
}
#define CHECKDIFF(p) if (ref_r->csr.p != cpu.csr.p) { \
  printf("\033[1;31m difftest fail at " #p ", expect %#x got %#x\033[0m\n", ref_r->csr.p, cpu.csr.p); \
  error = 1; \
}
#define CHECKDIFF_FMT(p, fmt, ...) if (ref_r->p != cpu.p) { \
  printf("difftest fail at " fmt ", expect %#x got %#x\n", ## __VA_ARGS__, ref_r->p, cpu.p); \
  error = 1; \
}

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  int error = 0;
  int reg_num = ARRLEN(cpu.gpr);
  for (int i = 0; i < reg_num; i++) {
    CHECKDIFF_FMT(gpr[i], "gpr[%d]", i);
  }
  CHECKDIFFPC(pc);
  if(error == 1)
  return false;
  else
  return true;
}

void isa_difftest_attach() {
}
