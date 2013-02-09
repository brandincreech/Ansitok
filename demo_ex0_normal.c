/** @file demo_ex0_normal.c
  * Demonstrate the normal way to use Ansitok
  *
  * See also: demo_ex0_compat.c
  * See also: http://linux.die.net/man/3/strtok for the example on which this
  * demonstration is based
  */
#include "standard_headers.h"
#include "Ansitok.h"

int main(void)
{
	char sentence[] = "/usr/local/bin: /usr/bin: /bin";
	char *token, *subtoken;
	
	Ansitok t = Ansitok_init(sentence, ":\t ", ANSITOK_OPT_SKIPEMPTY);
	for (int j = 1; (token = Ansitok_getNext(&t)) != NULL; j++) {
		printf("%d: %s\n", j, token);

		Ansitok st = Ansitok_init(token, "/", ANSITOK_OPT_SKIPEMPTY);
		while((subtoken = Ansitok_getNext(&st)) != NULL) {
			printf(" --> `%s'\n", subtoken);
		}
	}
	return EXIT_SUCCESS;
}
