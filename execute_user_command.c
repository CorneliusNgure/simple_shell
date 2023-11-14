#include "simple_shell.h"

/**
 * _strncmp - compares two strings up to n no. of characters.
 * @s1: the first string.
 * @s2: the second string.
 * @n: the maximum number of characters to compare.
 * Return:
 *   - 0 if the strings are equal,
 *   - a negative value if s1 is less than s2,
 *   - a positive value if s1 is greater than s2.
 */

int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; ++i)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return (s1[i] - s2[i]);
	}

	return (0);
}

/**
 * _isdigit - checks for a digit (0 through 9)
 *
 * @c: digit to be checked.
 *
 * Return: 1 if c is a digit and 0 otherwise.
 */

int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/**
 * _strcpy - Copies a string from source to destination.
 * @dest: The destination buffer.
 * @src: The source string to be copied.
 * Return: A pointer to the destination buffer.
 */

char *_strcpy(char *dest, const char *src)
{
	char *dest_start = dest;

	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = '\0';

	return (dest_start);
}

/**
 * run_user_command - runs the user command.
 * @input: the user input string command.
 */

void run_user_command(char *input)
{
	char *token;
	char *commands[BUFFER_SIZE];
	int i = 0, j;

	token = _strtok(input, ";");

	while (token != NULL && i < BUFFER_SIZE - 1)
	{
		commands[i] = token;
		token = _strtok(NULL, ";");
		i++;
	}

	commands[i] = NULL;

	for (j = 0; j < i; j++)
	{
		process_commands(commands[j]);
	}
}

/**
 * process_commands - splits string based on ; & executes commands individually.
 * @command: the user input string.
 */

void process_commands(char *command)
{
	char *token;
	char *args[BUFFER_SIZE];
	int i = 0;

	if (command != NULL)
	{
		token = _strtok(command, " ");
		if (token == NULL)
			return;
	}

	while (token != NULL && i < BUFFER_SIZE - 1)
	{
		args[i] = token;
		token = _strtok(NULL, " ");
		i++;
	}

	args[i] = NULL;

	execute_command(args);
}

/**
 * execute_command - tokenizes user input string into arguments.
 * @args: the user command string.
 */

void execute_command(char *args[])
{
	pid_t pid;
	int status, exit_status;
	char error_msg[] = "Command exited with error: ";
	char *full_error_msg, *exec_path;

	if (_strcmp(args[0], "exit") == 0)
	{
		exit_status = 0;

		if (args[1] != NULL)
		{
			exit_status = _atoi(args[1]);
		}

		exit_shell_with_status(exit_status);
	}
	else if (_strcmp(args[0], "_setenv") == 0)
	{
		if (args[1] != NULL && args[2] != NULL)
		{
			if (_setenv(args[1], args[2], 1) == 0)
				write_to_stdout("Environment variable set successfully.\n");
			else
				write_to_stdout("Failed to set environment variable.\n");
		}
		else
		{
			write_to_stdout("Usage: _setenv <name> <value>\n");
		}
	}
	else if (_strcmp(args[0], "_unsetenv") == 0)
	{
		if (args[1] != NULL)
		{
			if (_unsetenv(args[1]) == 0)
				write_to_stdout("Environment variable unset successfully.\n");
			else
				write_to_stdout("Failed to unset environment variable.\n");
		}
		else
			write_to_stdout("Usage: _unsetenv <name>\n");
	}
	else if (_strcmp(args[0], "cd") == 0)
	{
		cd_built_in(args);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			exec_path = get_env_path(args[0]);
			if (exec_path != NULL)
			{
				if (execve(exec_path, args, NULL) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				full_error_msg = malloc(_strlen(error_msg) + _strlen(args[0]) + 1);
				if (full_error_msg == NULL)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}

				_strcpy(full_error_msg, error_msg);
				_strcat(full_error_msg, args[0]);
				write_to_stdout(full_error_msg);
				free(full_error_msg);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}
}
