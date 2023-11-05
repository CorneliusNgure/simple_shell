#include "simple_shell.h"

/**
 * run_user_command - executes the user input command.
 * @command: the user input.
 *
 * Return: void.
 */

void run_user_command(const char *command)
{
	char args[] = {"/bin/sh", "-c", NULL, NULL};
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		args[2] = (char *)command;
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
			write_to_stdout("Command exited with status %d\n");
		}
	}
}
