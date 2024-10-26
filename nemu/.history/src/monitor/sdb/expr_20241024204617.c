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
#include<assert.h>
#include <regex.h>
#include<string.h>

enum {
  TK_NOTYPE = 256,
  NUM=1,
  HEX=2,
  EQ=3,
  NEQ=4,
  OR=5,
  AND=6,
  LEQ=7,
  GEQ=8,
  REGISTER=9,
  LPARE=10,
  RPARE=11,
  ADD=12,
  SUB=13,
  MUL=14,
  DIV=15
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  
  {" +", TK_NOTYPE},    // spaces
  {"\\+", ADD},         // plus
  {"\\-",SUB},
  {"\\*",MUL},
  {"\\/",DIV},

  {"\\(",LPARE},
  {"\\)",RPARE},

  {"\\<\\=", LEQ},
  {"\\>\\=",GEQ},
  {"\\=\\=",EQ},        
  {"\\!\\=",NEQ},

  {"\\&\\&",AND},
  {"\\|\\|",OR},

  {"\\$[a-zA-Z]*[0-9]*",REGISTER},

  {"0[xX][0-9a-fA-F]+",HEX},

  {"[0-9]*",NUM}
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
    for(int i=0;i<32;i++)
    {tokens[i].type=0;
     strcpy(tokens[i].str,"0");}
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
         case 12:
            tokens[nr_token++].type=12;
            break;
         case 13:
            tokens[nr_token++].type=13;
            break;
         case 14:
            tokens[nr_token++].type=14;
            break;
         case 15:
            tokens[nr_token++].type=15;
            break;
         case 256:
            break;
         case 1:
            tokens[nr_token].type=1;
            strncpy(tokens[nr_token].str,&e[position-substr_len],substr_len);
            nr_token++;
            break;
         case 2:
            tokens[nr_token].type = 2;
            strncpy(tokens[nr_token].str, &e[position - substr_len], substr_len);
            nr_token ++;
            break;
         case 3:
            tokens[nr_token++].type=3;
            break;
         case 4:
            tokens[nr_token++].type=4;
            break;
         case 5:
            tokens[nr_token++].type=5;
            break;
         case 6:
            tokens[nr_token++].type=6;
            break;
         case 7:
            tokens[nr_token++].type=7;
            break;
         case 8:
            tokens[nr_token++].type=8;
            break;
         case 10:
            tokens[nr_token++].type=8;
            break;
}

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  TODO();

  return 0;
}
