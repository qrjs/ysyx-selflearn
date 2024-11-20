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
#include <dlfcn.h>
#include <capstone/capstone.h>
#include <common.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static size_t (*cs_disasm_dl)(csh handle, const uint8_t *code,
    size_t code_size, uint64_t address, size_t count, cs_insn **insn);
static void (*cs_free_dl)(cs_insn *insn, size_t count);

static csh handle;

void init_disasm() {
  void *dl_handle;
  dl_handle = dlopen("/lib/libcapstone.so", RTLD_LAZY);
  if (!dl_handle) {
    fprintf(stderr, "Error loading libcapstone: %s\n", dlerror());
    exit(1);
  }

  cs_err (*cs_open_dl)(cs_arch arch, cs_mode mode, csh *handle) = NULL;
  cs_open_dl = dlsym(dl_handle, "cs_open");
  if (!cs_open_dl) {
    fprintf(stderr, "Error finding cs_open: %s\n", dlerror());
    exit(1);
  }

  cs_disasm_dl = dlsym(dl_handle, "cs_disasm");
  if (!cs_disasm_dl) {
    fprintf(stderr, "Error finding cs_disasm: %s\n", dlerror());
    exit(1);
  }

  cs_free_dl = dlsym(dl_handle, "cs_free");
  if (!cs_free_dl) {
    fprintf(stderr, "Error finding cs_free: %s\n", dlerror());
    exit(1);
  }

  // 强制使用 RISC-V 架构和模式
  cs_arch arch = CS_ARCH_RISCV;  // 强制使用 RISC-V 架构
  cs_mode mode = CS_MODE_RISCV32; // 强制使用 RISC-V 32 位模式

  int ret = cs_open_dl(arch, mode, &handle);
  if (ret != CS_ERR_OK) {
    fprintf(stderr, "Error initializing Capstone: %d\n", ret);
    exit(1);
  }

#ifdef CONFIG_ISA_x86
  cs_err (*cs_option_dl)(csh handle, cs_opt_type type, size_t value) = NULL;
  cs_option_dl = dlsym(dl_handle, "cs_option");
  if (!cs_option_dl) {
    fprintf(stderr, "Error finding cs_option: %s\n", dlerror());
    exit(1);
  }

  ret = cs_option_dl(handle, CS_OPT_SYNTAX, CS_OPT_SYNTAX_ATT);
  if (ret != CS_ERR_OK) {
    fprintf(stderr, "Error setting Capstone option: %d\n", ret);
    exit(1);
  }
#endif
}

void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte) {
  cs_insn *insn;
  size_t count = cs_disasm_dl(handle, code, nbyte, pc, 0, &insn);
  if (count != 1) {
    fprintf(stderr, "Disassembly failed\n");
    exit(1);
  }
  
  int ret = snprintf(str, size, "%s", insn->mnemonic);
  if (insn->op_str[0] != '\0') {
    snprintf(str + ret, size - ret, "\t%s", insn->op_str);
  }
  
  cs_free_dl(insn, count);
}
