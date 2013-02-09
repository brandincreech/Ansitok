/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="- This is, a sample , string.";
  char * pch;
  printf ("Tokenizing \"%s\":\n",str);
  pch = strtok (str," ,");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,");
  }
  return 0;
}
