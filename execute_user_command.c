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
 * run_user_command - executes the user input command.
 * @input: the user command.
 */

void run_user_command(char *input)
{
	int status, exit_status, i = 0;
	pid_t pid;
	char error_msg[] = "Command exited with error: ";
	char *full_error_msg, *token;
	char *args[BUFFER_SIZE], *exec_path;

	if (input != NULL)
	{
		token = _strtok(input, " ");
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

	if (_strcmp(args[0], "exit") == 0)
	{
		exit_status = 0;

		if (args[1] != NULL)
		{
			exit_status = _atoi(args[1]);
		}

		free(input);
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


/**
 * get_env_path - gets the PATH.
 * @command: user input command.
 *
 * Return: pointer to PATH.
 */

char *get_env_path(char *command)
{
	char *path = _getenv("PATH");
	char *token, *full_path;
	char delimiter[] = ":";

	token = _strtok(path, delimiter);

	while (token != NULL)
	{
		full_path = malloc(_strlen(token) + _strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		_strcpy(full_path, token);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}

		free(full_path);
		token = _strtok(NULL, delimiter);
	}
	return (NULL);
}
