#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define BUFFER_SIZE 1024

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stddef.h>

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
char *get_env_path(char *command);
const char *_strchr(const char *s, char c);
int is_delimiter(char c, const char *delim);
char *_strtok(char *str, const char *delim);
int _strncmp(char *s1, char *s2, size_t n);
int _isdigit(int c);
void exit_shell_with_status(int status);
int _atoi(const char *str);
int _strcmp(char *s1, char *s2);
void run_user_command(char *input);
void cd_built_in(char **args);
size_t _strcspn(const char *s, const char *reject);
char *_getenv(char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

#endif
