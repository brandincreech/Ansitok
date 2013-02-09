#include <stdio.h>
#include <string.h>
#include "Ansitok.h"
 
// Delimiter values
#define DELIM " ,.-+"
 
int main (void)
{
  char str_to_tokenize[] = "- Strtok is used to - break up, strings with funny values. + 5";
  char *str_ptr;
 
  fprintf(stdout, "Tokenizing \"%s\":\n", str_to_tokenize);
 
  Ansitok at = Ansitok_init(str_to_tokenize, DELIM, ANSITOK_OPT_SKIPEMPTY);
  str_ptr = Ansitok_getNext(&at);
  for(; str_ptr != NULL ;){
    fprintf(stdout, "%s\n", str_ptr);
    str_ptr = Ansitok_getNext(&at);
  }
  Ansitok_done(&at);
  
  return 0;
}
