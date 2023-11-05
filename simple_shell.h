#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void write_to_stdout(const char *outputText);
char *readUserInput();
void run_user_command(char *command);

#endif
