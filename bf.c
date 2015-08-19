#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef CODESIZE
#define CODESIZE 100000
#endif

/* remove pointless parts */
void cleancode (char * code) {
  char *str, *tmp;
  unsigned int lvl = 0;

  while (1) {
    if ((str = strstr(code, "<>")) || (str = strstr(code, "><")) ||
        (str = strstr(code, "+-")) || (str = strstr(code, "-+"))) {
      /* strip two bytes, shift the rest */
      while ((*str = *(str+2))) str++;
    }
    /* starting loops are skipped */
    else if (code[0] == '[') {
      tmp = str = code;
      lvl = 0;
      while (*str) {
        if (*str == '[') lvl++;
        else if (*str == ']') lvl--;
        str++;
        if (lvl == 0) break;
      }
      while ((*(tmp++) = *(str++))) ;
    }
    /* loops that follow other loops are skipped */
    else if ((str = strstr(code, "]["))) {
      /* basically the same as above */
      tmp = str;
      lvl = 0;
      while (*(++str)) {
        if (*str == '[') lvl++;
        else if (*str == ']') lvl--;
        if (lvl == 0) break;
      }
      while ((*(tmp++) = *(str++))) ;
    }
    else break;
  }
}

void readcode (char * code) {
  int c, i = 0;
  while ((c = getchar()) != EOF && i < CODESIZE - 1) {
    switch (c) {
      case '.': case ',': case '>': case '<':
      case '+': case '-': case '[': case ']':
        code[i++] = c;
    }
  }
}

int main () {
#ifdef HEAP
  char *code = calloc(CODESIZE, sizeof(char));
#else
  char code[CODESIZE] = { 0 };
#endif

  readcode(code);
  cleancode(code);
  puts(code);

  return 0;
}
