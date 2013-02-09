#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Ansitok.h"

static char s[1000] = "";
static char r[1000] = "";

int main()
{
	fgets(s, 1000, stdin);
	if (s[strlen(s)-1] == '\n')
		s[strlen(s)-1] = '\0';

	char *sentence;
	Ansitok at = Ansitok_init(s, ".", ANSITOK_OPT_DEFAULT);
	while ((sentence = Ansitok_getNext(&at)) != NULL) {
		if (*sentence == '\0') continue;
		printf("sentence found: \"%s\"\n", sentence);
		{
			strcpy(r,sentence);
			Ansitok atat = Ansitok_init(r, " ", ANSITOK_OPT_DEFAULT);
			char *word;
			while ((word = Ansitok_getNext(&atat)) != NULL) {
				if (*word == '\0') continue;
				printf("\tword: `%s'\n", word);
			}
			Ansitok_done(&atat);
		}
	}
	Ansitok_done(&at);
	
	return 0;
}
