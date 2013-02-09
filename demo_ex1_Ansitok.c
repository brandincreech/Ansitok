/* strtok example */
#include <stdio.h>
#include <string.h>
#include "Ansitok.h"

int main (void)
{
  char str[] ="- This is, a sample , string.";
  char * pch;
  printf ("Tokenizing \"%s\":\n",str);
  Ansitok th = Ansitok_init(str, " ,", ANSITOK_OPT_SKIPEMPTY);
  while ((pch = Ansitok_getNext(&th)) != NULL) {
    printf("%s\n", pch);
  }
  return 0;
}
