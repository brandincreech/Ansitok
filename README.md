Ansitok
=======

Ansitok - string tokenization that is like ANSI strtok.

It operates differently from strtok but is intended to be straightforward
to convert code from using strtok to using Ansitok. The demo files are 
written in pairs in order to demonstrate the difference:

demo_FOO_strtok.c - Demonstrate doing some FOO using strtok
demo_FOO_Ansitok.c - Demonstrate doing the same FOO using Ansitok

EXAMPLE USAGE
=============

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
