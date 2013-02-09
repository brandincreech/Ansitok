#include "Ansitok.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define _(VAR) _private_ ## VAR
static void Ansitok_seekNext_(Ansitok *t);
static bool Ansitok_equals_(const Ansitok a, const Ansitok b);
static void Ansitok_queueNext_(Ansitok *t);
static char *Ansitok_getNext_(Ansitok *t);

Ansitok Ansitok_init(char *s, const char *delim, unsigned optflags)
{
	Ansitok t = (Ansitok){
		._(str) = s, 
		._(delim) = delim, 
		._(endchar) = '\0', 
		._(endpos) = -1,
		._(strlen) = strlen(s),
		._(begpos) = 0,
		._(firstrun) = true,
		._(skipempty) = false,
		._(queuedtoken) = NULL,
		._(hasnext) = true,
	};
	if (optflags | ANSITOK_OPT_SKIPEMPTY)
		t._(skipempty) = true;
	Ansitok_queueNext_(&t);
	return t;
}

static bool Ansitok_equals_(const Ansitok a, const Ansitok b)
{
	if (strcmp(a._(str), b._(str)) != 0) return false;
	if (a._(delim) != b._(delim)) return false;
	if (a._(endchar) != b._(endchar)) return false;
	if (a._(endpos) != b._(endpos)) return false;
	if (a._(begpos) != b._(begpos)) return false;
	if (a._(strlen) != b._(strlen)) return false;
	if (a._(firstrun) != b._(firstrun)) return false;
	if (a._(skipempty) != b._(skipempty)) return false;
	if (a._(queuedtoken) != b._(queuedtoken)) return false;
	if (a._(hasnext) != b._(hasnext)) return false;
	return true;
}

char *Ansitok_strtok(char *s, const char *delim, Ansitok *t) {
	if (s != NULL) { // then this is the first call using t
		*t = Ansitok_init(s, delim, ANSITOK_OPT_SKIPEMPTY);
	}
	return Ansitok_getNext(t);
}

void Ansitok_done(Ansitok *t)
{
	assert(!Ansitok_equals_(*t, ANSITOK_0));
	while (Ansitok_getNext(t) != NULL)
		;
	*t = ANSITOK_0;
}

char Ansitok_identifyDelim(Ansitok *t)
{
	return t->_(endchar);
}

bool Ansitok_hasNext(Ansitok *t)
{
	return t->_(hasnext);
}

static void Ansitok_seekNext_(Ansitok *t)
{
	t->_(endpos)++;
	t->_(begpos) = t->_(endpos);
	for (; t->_(endpos) < t->_(strlen); t->_(endpos)++) {
		for (size_t i=0; i < strlen(t->_(delim)); i++)
			if (t->_(str)[t->_(endpos)] == t->_(delim)[i]) {
				t->_(endchar) = t->_(str)[t->_(endpos)]; // Save endchar
				t->_(str)[t->_(endpos)] = '\0';
				return;  // then we found a token
			}
	}
	t->_(endchar) = '\0';
}

static char *
Ansitok_getNext_(Ansitok *t)
{
	char *token;
	for(;;) {
		if (!(t->_(endpos)+1 < t->_(strlen))) // no token found
			return NULL;
		
		if (!t->_(firstrun))
			t->_(str)[t->_(endpos)] = t->_(endchar); // Restore endchar
		else
			t->_(firstrun) = false;
		Ansitok_seekNext_(t);
		token = &(t->_(str)[t->_(begpos)]);

		if (t->_(skipempty) == false || strlen(token) > 0)
			break;
	}
	return token;
}

static void
Ansitok_queueNext_(Ansitok *t)
{
	if (t->_(queuedtoken) != NULL)
		return;
	if (t->_(hasnext) == false)
		return;
		
	char *token = Ansitok_getNext_(t);
	if (token==NULL) {
		t->_(hasnext) = false;
		t->_(queuedtoken) = NULL;
	}else{
		t->_(hasnext) = true;
		t->_(queuedtoken) = token;
	}
}

char *
Ansitok_getNext(Ansitok *t)
{
	Ansitok_queueNext_(t);
	char *token = t->_(queuedtoken);
	t->_(queuedtoken) = NULL;
	return token;
}
