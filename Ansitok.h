/** @file Ansitok.h
  * Ansitok - Provide string tokenization in a similar manner to ANSI strtok(3)
  *
  * It operates differently from strtok but is intended to be straightforward
  * to convert code from using strtok to using Ansitok. The demo files are 
  * written in pairs in order to demonstrate the difference:
  *
  * demo_FOO_strtok.c - Demonstrate doing some FOO using strtok
  * demo_FOO_Ansitok.c - Demonstrate doing the same FOO using Ansitok
  *
  */
#include <stdbool.h>
#include <stdlib.h>

#define ANSITOK_OPT_DEFAULT (0)
#define ANSITOK_OPT_SKIPEMPTY (1)

struct Ansitok;
typedef struct Ansitok Ansitok;

// Ansitok_init - Initialize a new Ansitok handle
// An optflags value of ANSITOK_OPT_SKIPEMPTY causes empty tokens to be skipped
// automatically. If optflags is ANSITOK_OPT_DEFAULT, the default behavior is
// used and empty tokens are returned if they exist.
//
// EXAMPLE USAGE
//   char sentence[] = "/usr/local/bin: /usr/bin: /bin";
//   char *token, *subtoken;
//   
//   Ansitok t = Ansitok_init(sentence, ":\t ", ANSITOK_OPT_SKIPEMPTY);
//   for (int j = 1; (token = Ansitok_getNext(&t)) != NULL; j++) {
//     printf("%d: %s\n", j, token);
//     Ansitok st = Ansitok_init(token, "/", ANSITOK_OPT_SKIPEMPTY);
//     while((subtoken = Ansitok_getNext(&st)) != NULL) {
//       printf(" --> `%s'\n", subtoken);
//     }
//   }
Ansitok Ansitok_init(char *s, const char *delim, unsigned optflags);

// Ansitok_strtok - Behave in a strtok(3)-like fashion. This means that
// the first call to Ansitok_strtok will initialize the handle as well as 
// fetch the first token, if it exists. Because of this, the initial call
// to Ansitok_strtok must be called with s != NULL, and all subsequent calls
// must be called with s == NULL. This is the requirement of strtok(3) as well.
//
// The example from Ansitok_init is rewritten below using this interface. See 
// also the example on 
// http://linux.die.net/man/3/strtok , which uses strtok_r instead.
//
// USAGE
//   char sentence[] = "/usr/local/bin: /usr/bin: /bin";
//   char *token, *subtoken;
//   char *str, *substr;
//   Ansitok t, st;
//   
//   int j;
//   for (j = 1, str = sentence; ;j++, str = NULL) {
//     token = Ansitok_strtok(str, ":\t ", &t);
//     if (token == NULL)
//       break;
//     printf("%d: %s\n", j, token);
//
//     for (substr = token; ; substr = NULL) {
//       subtoken = Ansitok_strtok(substr, "/", &st);
//       if (subtoken == NULL)
//         break;
//       printf(" --> `%s'\n", subtoken);
//     }
//   }
char *Ansitok_strtok(char *s, const char *delim, Ansitok *t);

// Ansitok_done - Clean up the string which was handled by Ansitok handle t.
// This call signals the end of life of the Ansitok handle. Using it is 
// recommended but not required. In particular, if the value NULL was already
// received by calling Ansitok_getNext then this function performs no action
// except for marking the token as "finished". However, it is only allowed that
// Ansitok_done be called exactly once for the handle. Otherwise, a failed 
// assertion results.
//
// EXAMPLE USAGE
//   Ansitok t = Ansitok_init(sentence, delim);
//   ...
//   Ansitok_done(&t);
void Ansitok_done(Ansitok *t);

// Ansitok_hasNext - return true if the string handled by t has more tokens
//
// EXAMPLE USAGE
//   if (Ansitok_hasNext(&t))
//     printf("There are more tokens\n");
bool Ansitok_hasNext(Ansitok *t);

// Ansitok_getNext - return the next token or NULL if no more tokens exist
//
// EXAMPLE USAGE
//   char *tok = Ansitok_getNext(&t);
//   printf("The first token is `%s'\n", tok);
//   tok = Ansitok_getNext(&t);
//   printf("The second token is `%s'\n", tok);
char *Ansitok_getNext(Ansitok *t);

// Ansitok_identifyDelim - identify the first delimiter used when fetching the
// current token
//
// EXAMPLE USAGE
//   char sentence[] = "Hello, world.";
//   Ansitok t = Ansitok_init(sentence, ".,", NULL);
//   char *w = Ansitok_getNext(&t);
//   printf("Word 1 has a delimiter of '%c'\n", w, Ansitok_identifyDelim(&t));
//   w = Ansitok_getNext(&t);
//   printf("Word 2 has a delimiter of '%c'\n", w, Ansitok_identifyDelim(&t));
char Ansitok_identifyDelim(Ansitok *t);

// -----------------------------------------------------------------------------
// You shall not pass!
// -----------------------------------------------------------------------------
struct Ansitok {
	char *_private_str;
	const char *_private_delim;
	char _private_endchar;
	size_t _private_endpos;
	size_t _private_begpos;
	size_t _private_strlen;
	bool _private_firstrun;
	bool _private_skipempty;
	char *_private_queuedtoken;
	bool _private_hasnext;
};

#define ANSITOK_0 (Ansitok) {._private_str=""}
