#ifndef _hsh_h_
#define _hsh_h_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void display_prompt(void);
char *read_input(void);
void execute_command(char *command);
void cleanup(char *line);

#endif
