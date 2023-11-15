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
 * process_commands - splits string based on ; & executes commands individually
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
 * execute_external_command - runs non-built-in command.
 * @args: the array of command and arguments.
 */

void execute_external_command(char *args[])
{
	pid_t pid;
	int status;
	char *exec_path;

	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (args[0][0] == '/')
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			exec_path = get_env_path(args[0]);
			if (exec_path != NULL)
			{
				if (execve(exec_path, args, NULL) == -1)
				{
					write_to_stdout("Command exited with error: ");
					write_to_stdout(args[0]);
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				write_to_stdout("Command not found: ");
				write_to_stdout(args[0]);
				exit(EXIT_FAILURE);
			}
		}
	}
	else
		wait(&status);
}

/**
 * execute_command - determines whether the command is a built-in command,
 * or an external program and calls the corresponding function.
 *
 * @args: the array of command and arguments.
 */

void execute_command(char *args[])
{
	int exit_status;

	if (_strcmp(args[0], "exit") == 0)
	{
		exit_status = (args[1] != NULL) ? _atoi(args[1]) : 0;
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
			write_to_stdout("Usage: _setenv <name> <value>\n");
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
		cd_built_in(args);
	else
		execute_external_command(args);
}
