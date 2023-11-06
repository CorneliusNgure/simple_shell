#include "simple_shell.h"

/**
 * printCurrent_env_vars - prints the current environment variables.
 *
 */

void printCurrent_env_vars(void)
{
	int i = 0;
	char *env_var;
	extern char **environ;

	while (1)
	{
		if (environ != NULL)
		{
			env_var = environ[i];
		}
		if (env_var == NULL)
			break;

		write_to_stdout(env_var);
		write_to_stdout("\n");
		i++;
	}
}

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
			else if (_strcmp(input, "env") == 0)
			{
				free(input);
				printCurrent_env_vars();
			}
			else
			{
				run_user_command(input);
				free(input);
			}
		}
	}
	return (0);
}
