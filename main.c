#include "simple_shell.h"

/**
 * _strcmp - function that compares two strings.
 *
 * @s1: string 1.
 * @s2: string 2.
 *
 * Return: 0.
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}

	return (0);
}

/**
 * exit_shell - Exit the shell.
 */
void exit_shell(void)
{
	write_to_stdout("Exiting the shell...\n");
	exit(0);
}

/**
 * main - entry point.
 *
 * Return: Always 0.
 */

int main(void)
{
	char *input;

	while (1)
	{
		write_to_stdout("kings_shell$$> ");
		input = readUserInput();

		if (input != NULL)
		{
			if (_strcmp(input, "exit") == 0)
			{
				free(input);
				exit_shell();
			}

			run_user_command(input);
			free(input);
		}
	}

	return (0);
}
