#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define BUFFER_SIZE 1024

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void write_to_stdout(const char *outputText);
char *readUserInput();
char *_strdup(const char *src);
char *_strncpy(char *dest, const char *src, int n);
char *_strcpy(char *dest, const char *src);
int _strlen(const char *s);
char *_strcat(char *dest, char *src);
void run_user_command(char *command);
void exit_shell(void);
void printCurrent_env_vars(void);
char *custom_getline(void);
void get_env_path(char *command)

#endif
