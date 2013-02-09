#include "standard_headers.h"
#include "Ansitok.h"

int main(void)
{
	char sentence[] = "Hello, world.";
	Ansitok t = Ansitok_init(sentence, ", ", ANSITOK_OPT_DEFAULT);

	Ansitok_getNext(&t);
	printf("The first token is %s\n", Ansitok_peekToken(&t));
	printf("The first token has length %d\n", strlen(Ansitok_peekToken(&t)));
	Ansitok_getNext(&t);
	printf("The second token is %s\n", Ansitok_peekToken(&t));
	printf("The second token has length %d\n", strlen(Ansitok_peekToken(&t)));

	return EXIT_SUCCESS;
}