#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
    size_t len = 0;
    while (s[len] != '\0') {  // 遍历直到遇到空字符
        len++;
    }
    return len;
}


char *strcpy(char *dst, const char *src) {
  char *d=dst;
  while(*src !='\0'){
     *d=*src;
     d++;
     src++;      
  }
   *d = '\0';  
    return dst;  
}

char *strncpy(char *dst, const char *src, size_t n) {
 char *d=dst;
 while(*src!='\0' && n>0){
     *d=*src;
     d++;
     src++;
     n--;
 }
 *d='\0';
 return dst;

}

char *strcat(char *dst, const char *src) {
  char *d=dst;
  while(*d!='\0'){
      d++;
  }
  while(*src!='\0'){
      *d=*src;
      d++;
      src++;
  }
  *d='\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  while(*s1!='\0' && *s2!='\0'){
      if(*s1!=*s2){
          return *s1-*s2;
      }
      s1++;
      s2++;
  }
  return *s1-*s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  while(*s1!='\0' && *s2!='\0' && n>0){
      if(*s1!=*s2){
          return *s1-*s2;
      }
      s1++;
      s2++;
      n--;
  }
  return *s1-*s2;
}

void *memset(void *s, int c, size_t n) {
  char *p=s;
  while(n>0){
      *p=c;
      p++;
      n--;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  char *d=dst;
  const char *s=src;
  if(d<s){
      while(n>0){
          *d=*s;
          d++;
          s++;
          n--;
      }
  }else{
      d=d+n-1;
      s=s+n-1;
      while(n>0){
          *d=*s;
          d--;
          s--;
          n--;
      }
  }
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  char *d=out;
  const char *s=in;
  while(n>0){
      *d=*s;
      d++;
      s++;
      n--;
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const char *p1 = s1;
    const char *p2 = s2;
      while (n > 0){
        if (*p1 != *p2){
            return *p1 - *p2;
        }
        p1++;
        p2++;
        n--;
      }
      return 0;
}

#endif
