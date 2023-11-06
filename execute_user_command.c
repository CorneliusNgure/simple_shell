#include "simple_shell.h"
/**
 * run_user_command - executes the user input command.
 * @command: the user input.
 * Return: void.
 */
void run_user_command(char *command)
{
	char *args[] = {"/bin/sh", "-c", NULL, NULL};
	int status;
	pid_t pid;
	char error_msg[] = "Command exited with error: ", *full_error_msg;

	if (access(command, X_OK) == -1)
	{
		write_to_stdout("Command does not exist or not executable\n");
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		args[2] = command;
		if (execve("/bin/sh", args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (WEXITSTATUS(status) && WEXITSTATUS(status) != 0)
		{
			full_error_msg = malloc(_strlen(error_msg) + _strlen(command) + 1);
			if (full_error_msg == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			_strcpy(full_error_msg, error_msg);
			_strcat(full_error_msg, command);
			write_to_stdout(full_error_msg);
			free(full_error_msg);
		}
	}
}
