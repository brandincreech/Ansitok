#include <stdio.h>
#include <string.h>
 
// Delimiter values
#define DELIM " ,.-+"
 
int main (void)
{
  char str_to_tokenize[] = "- Strtok is used to - break up, strings with funny values. + 5";
  char *str_ptr;
 
  fprintf(stdout, "Tokenizing \"%s\":\n", str_to_tokenize);
 
  str_ptr = strtok(str_to_tokenize, DELIM);
  for(; str_ptr != NULL ;){
    fprintf(stdout, "%s\n", str_ptr);
    str_ptr = strtok(NULL, DELIM);
  }
 
  return 0;
}
