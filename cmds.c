/******************************************************************
*
*   file:     cmds.c
*   author:   betty o'neil
*   date:     ?
*
*   semantic actions for commands called by tutor (cs341, hw2)
*
*   revisions:
*      9/90  eb   cleanup, convert function declarations to ansi
*      9/91  eb   changes so that this can be used for hw1
*      9/02  re   minor changes to quit command
*/
/* the Makefile arranges that #include <..> searches in the right
   places for these headers-- 200920*/

#include <stdio.h>
#include "slex.h"

/*===================================================================*
*
*   Command table for tutor program -- an array of structures of type
*   cmd -- for each command provide the token, the function to call when
*   that token is found, and the help message.
*
*   slex.h contains the typdef for struct cmd, and declares the
*   cmds array as extern to all the other parts of the program.
*   Code in slex.c parses user input command line and calls the
*   requested semantic action, passing a pointer to the cmd struct
*   and any arguments the user may have entered.
*
*===================================================================*/

PROTOTYPE int stop(Cmd *cp, char *arguments);
PROTOTYPE int mem_display(Cmd *cp, char *arguments);
PROTOTYPE int mem_set(Cmd *cp, char *arguments);
PROTOTYPE int help(Cmd *cp, char *arguments);

/* command table */

Cmd cmds[] = {{"md",  mem_display, "Memory display: MD <addr>"},
			  {"ms",  mem_set, "Memory set: MS<addr><value>"},
			  {"h",   help,        "Help: H <command>"},
              {"s",   stop,        "Stop" },
              {NULL,  NULL,        NULL}};  /* null cmd to flag end of table */

char xyz = 6;  /* test global variable  */
char *pxyz = &xyz;  /* test pointer to xyz */
/*===================================================================*
*		command			routines
*
*   Each command routine is called with 2 args, the remaining
*   part of the line to parse and a pointer to the struct cmd for this
*   command. Each returns 0 for continue or 1 for all-done.
*
*===================================================================*/

int stop(Cmd *cp, char *arguments) {
	return 1;			/* all done flag */
}

/*===================================================================*
*
*   mem_display: display contents of 16 bytes in hex
*
*/
int help(Cmd *cp, char *arguments) {
	char input[20];
	sscanf(arguments, "%s", input);
	if((strcmp("md", input)) == 0) {
		printf("Memory display: MD <addr> \n");
	}
	else if((strcmp("ms", input)) == 0) {
		printf("Memory set: MS<addr><value> \n");
	}
	else if((strcmp("h", input)) == 0) {
		printf("Help: H <command> \n");
	}
	else if((strcmp("s", input)) == 0) {
		printf("Stop \n");
	}
	else {
		printf("Memory display: MD <addr> \n");
		printf("Memory set: MS<addr><value> \n");
		printf("Help: H <command> \n");
		printf("Stop \n");
	}
	return 0;
}

int mem_display(Cmd *cp, char *arguments) {
	unsigned char *ptr;
	int location = 0;
	int num;

	sscanf(arguments, "%x", &location);
	printf("%08x ", location);

	ptr = (char *)location;

	for (num = 0; num < 16; num = num + 1) {
		printf("%02x ", *ptr);
		ptr = ptr + 1;
	}

	for(num = 0; num < 16; num = num + 1) {
		if((*ptr++) >= 0x20 && (*ptr++) <= 0x7e) {
			printf("%c", *(ptr + num));
		}
		else {
			printf(".");
		}
	}

	printf("\n");
	printf("Reached mem_display, passed argument string: |%s|\n", arguments);
	printf("        help message: %s\n", cp->help);
	return 0;	
}

int mem_set(Cmd *cp, char * arguments) {
	int old = 0;
	int new = 0;
	char *ptr;
	if(sscanf(arguments,"%x %x", &old, &new) == 2) {
		ptr = (unsigned char *)old;
		*ptr = new;
	}	
	else {
		printf("Error \n");
	}
	return 0;
}