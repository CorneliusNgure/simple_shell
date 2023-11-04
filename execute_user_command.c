#include "simple_shell.h"

/**
 * run_user_command - executes the user input command.
 * @command: the user input.
 *
 * Return: void.
 */

void run_user_command(const char *command)
{
	char *args[];
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror(fork);
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		args[] = {"/bin/sh", "-c", (char *)command, NULL};
		if (execve("/bin/sh", args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) != 0)
				{
					write_to_stdout("COmmand exited with status %d\n", WEXITSTATUS(status));
				}
			}
		}
}
