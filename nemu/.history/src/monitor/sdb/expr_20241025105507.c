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
            tokens[nr_token++].type='+';
            break;
         case 13:
            tokens[nr_token++].type='-';
            break;
         case 14:
            tokens[nr_token++].type='*';
            break;
         case 15:
            tokens[nr_token++].type='/';
            break;
         case 256:
            break;
         case 3:
            tokens[nr_token++].type='==';
            break;
         case 4:
            tokens[nr_token++].type='!=';
            break;
         case 5:
            tokens[nr_token++].type='||';
            break;
         case 6:
            tokens[nr_token++].type='&&';
            break;
         case 7:
            tokens[nr_token++].type='<=';
            break;
         case 8:
            tokens[nr_token++].type='>=';
            break;
         case 10:
            tokens[nr_token++].type='(';
            break;
         case 11:
            tokens[nr_token++].type=')';
            break;

//special
         case 1://NUM
            tokens[nr_token].type=NUM;
            strncpy(tokens[nr_token].str,&e[position-substr_len],substr_len);
            nr_token++;
            break;
         case 2://HEX
            tokens[nr_token].type = HEX;
            strncpy(tokens[nr_token].str, &e[position - substr_len], substr_len);
            nr_token ++;
            break;
         case 9://REGISTER
            tokens[nr_token].type = REGISTER;
            strncpy(tokens[nr_token].str, &e[position - substr_len], substr_len);
            nr_token ++;
            break;
         default:
            printf("i = %d and No rules is com.\n", i);
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




//pre_process
int tokens_len=0;
for(int i=0;i<31;i++)
{
  if(tokens[i].type==0)
  break;
  tokens_len++;
}


//init the register
for (int i=0;i<tokens_len;i++)
{
  if(tokens[i].type==REGISTER)
  {
    bool flag =true;
    int tmp=isa_reg_str2val(tokens[i].str,&flag);
    if(flag){
      int2char(tmp, tokens[i].str); // transfrom the str --> $egx
	    }else{
    printf("Transfrom error. \n");
		assert(0);
	}
  }
}


//init the hex
for (i=0;i<tokens_len;i++)
{
  if(tokens[i].type==HEX)
  {
    int value=strtol(tokens[i].str,NULL,16);
    int2char(value,tokens[i].str);
  }
}


//sub'-'-->negtive'-'
for(i=0;i<tokens_len;i++)
{
  if((tokens[i].type=='-' && i>0 &&\
  (tokens[i-1].type!=NUM && tokens[i-1].type!=HEX && tokens[i-1].type!=REGISTER && tokens[i-1].type!=RPARE)&&\
  (tokens[i+1].type==NUM || tokens[i+1].type==HEX || tokens[i+1].type==REGISTER))
  ||
  (tokens[i].type=='-' && i=0)
  )
  {
    tokens[i].type=TK_NOTYPE;
    for(j=31;j>=0;j--){
      tokens[i+1].str[j]=tokens[i+1].str[j-1];
    }
    tokens[i+1].str[0]='-';
    for(j=0;j<tokens_len;j++){
    if(tokens[j].type==TK_NOTYPE){
      for(int k=j+1;k<tokens_len;k++){
        tokens[k-1]=tokens[k];
      }
      tokens_len--;
    }
    }
  }
  return tokens_len;
}

//jie zhi zhen
//recongize multiple or jie yin yong
for (int i=0;i<tokens_len;i++)
{
  if(	(tokens[i].type == '*' && i > 0
      && tokens[i-1].type != NUM && tokens[i-1].type != HEX 
      && tokens[i-1].type != REGISTER && tokens[i-1].type != RPARE 
		    && (tokens[i+1].type == NUM || tokens[i+1].type == HEX || tokens[i+1].type == REGISTER)
		    )
		||
            (tokens[i].type == '*' && i == 0)
          )
  {
    tokens[i].type=TK_NOTYPE;
    uint32_t tmp=char2int(tokens[i+1].str);
    uint32_t value=*(uint32_t*(long)tmp);
    int2char(value,tokens[i+1].str);

    for (int j=0;j<tokens_len;j++){
      if(tokens[j].type==TK_NOTYPE){
        for(k=j+1;k<tokens_len;k++){
          tokens[k-1]=tokens[k];
        }
        tokens_len--;
      }
    }
  }
}


bool check_parentheses(int p,int q)
{
  if (tokens[p].type==LPARE && tokens[q].type==RPARE)
  {
    int par=0;

    for(int i=p;i<=q;i++)
    {
      if(tokens[i].type==LPARE)par++;
      else if(tokens[i].type==RPARE)par--;




      if(par==0)
      {
        if{i==q}
          return true;
        else
          return false;
      }




    }
  }
  return false;
}


//char to int 
unit32_t char2int(char s[])
{
  unit32_t res=0;
  for (int i=0;s[i]!='\0';i++)
  {
    res*=10;
    res+=s[i]-'0';
  }
  return res;
}

//int to char
void int2char(uint32_t num,char ret[])
{
 ret[0]='\0';
 char *p=ret;
 do{
  int temp=0;
  int temp=num%10;
  *(p++)=temp+'0';
  num/=10;
 }while(num)

 //reverse
 int len=strlen(ret);
 for (int i=0;i<len/2;i++)
 {
  char temp=ret[i];
  ret[i]=ret[(len-1-i)];
  ret[(len-1-i)]=temp;
 }


}

uint32_t eval(int p,int q)
{
  if(p==q)
  {
    uint32_t result=strtol(tokens[p].str,NULL,10);
    return result;
  }

  else if(check_parentheses(p,q)==true)
  {
    return eval(p+1,q-1);
  }

  else
  {
    int lpare_num=0;

    int op=31;

    int op_md=0;//mul or div

    bool flag=false;

    bool flag_md=false;

    for (int i=q;i>=p;i--)
    {
      if(tokens[i].type==RPARE)
      {
       if(tokens[i].type!=LPARE || lpare_num!=1)
       if (tokens[i].type==RPARE)
       lpare_num++;
       if(tokens[i].type==LPARE)
       lpare_num--;
       if(i==0)break;
       i--;
      }
       if(!flag && tokens[i].type == '||' ){
                flag = true;
                op = min(op,i);
            }

            if(!flag && tokens[i].type == '&&' ){
				        flag = true;
                op = min(op,i);
            }

            if(!flag && tokens[i].type == '!='){
                flag = true;
                op = min(op,i);
            }

            if(!flag && tokens[i].type == '=='){
                flag = true;
                op = min(op,i);
            }
            if(!flag && tokens[i].type == '<='){
                flag = true;
                op = min(op, i);
            }
            if(!flag && tokens[i].type == '>='){
                flag = true;
                op = min(op, i);
            }
             if(!flag && tokens[i].type == '+'){
                flag = true;
                op = min(op, i);
            }
            if(!flag && tokens[i].type == '-'){
                flag = true;
                op = min(op, i);
            }
            if(!flag && !flag_pd && tokens[i].type == '*'){
                flag_pd=true;
                op_pd=i;
                op = min(op, i);
            }
            if(!flag && !flag_pd && tokens[i].type == '/'){
                flag_pd=true;
                op_pd=i;
                op = min(op, i);
            }
    }
        if(flag==false)op_md=op;
        
        int op_type=tokens[op].type;

        uint32_t val1=eval(p,op-1);
        unit32_t val2=eval(op+1,q);

        int32_t resu_tmp;//val1_tmp+val2_tmp
        int32_t val1_tmp;
        int32_t val2_tmp;
        

        swith (op_type)
        {
          case '+':
          return val1+val2;
          case '-':
          return val1-val2;
          case '*':
          {
            val1_tmp=(int32_t)val1;
            val2_tmp=(int32_t)val2;
            resu_tmp=val1_tmp*val2_tmp;
            return (uint32_t)resu_tmp;
          }
          case '/':
          if(val2==0){
            printf("division can't be zero;\n");
            return 0;
          }
           val1_tmp=(int32_t)val1;
            val2_tmp=(int32_t)val2;
                resu_tmp=val1_tmp/val2_tmp;

                return (uint32_t)resu_tmp;
        }
  }
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
