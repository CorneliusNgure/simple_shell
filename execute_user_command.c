#include "simple_shell.h"

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
	int status, i = 0;
	pid_t pid;
	char error_msg[] = "Command exited with error: ";
	char *full_error_msg, *token = _strtok(input, " ");
	char *args[BUFFER_SIZE], *exec_path;

	if (token == NULL)
		return;

	while (token != NULL && i < BUFFER_SIZE - 1)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;

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

/**
 * get_env_path - gets the PATH.
 * @command: user input command.
 *
 * Return: pointer to PATH.
 */

char *get_env_path(char *command)
{
	char *path = getenv("PATH");
	char *token, *full_path;
	char delimiter[] = ":";

	token = strtok(path, delimiter);

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
		token = strtok(NULL, delimiter);
	}
	return (NULL);
}
