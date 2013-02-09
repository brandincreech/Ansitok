/** @file demo_ex0_compat.c
  * Demonstrate the compatibility function Ansitok_strtok
  *
  * See also: demo_ex0_normal.c
  * See also: http://linux.die.net/man/3/strtok for the example on which this
  * demonstration is based
  */
#include "standard_headers.h"
#include "Ansitok.h"

int main(void)
{
  char sentence[] = "/usr/local/bin: /usr/bin: /bin";
  char *token, *subtoken;
  char *str, *substr;
  Ansitok t, st;
  
  int j;
  for (j = 1, str = sentence; ;j++, str = NULL) {
    token = Ansitok_strtok(str, ":\t ", &t);
    if (token == NULL)
      break;
    printf("%d: %s\n", j, token);

    for (substr = token; ; substr = NULL) {
      subtoken = Ansitok_strtok(substr, "/", &st);
      if (subtoken == NULL)
        break;
      printf(" --> `%s'\n", subtoken);
    }
  }
	return EXIT_SUCCESS;
}
