#include "simple_shell.h"

/**
 * _atoi - converts a string to an integer.
 * @str: the string to convert.
 * Return: the converted integer.
 */

int _atoi(const char *str)
{
	int result = 0;
	int sign = 1;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;

	if (*str == '-' || *str == '+')
	{
		sign = (*str == '-') ? -1 : 1;
		str++;
	}

	while (_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	return (sign * result);
}

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
	write_to_stdout("Exiting kings_shell$$...\n");
	exit(0);
}

/**
 * main - entry point.
 *
 * Return: Always 0.
 */

int main(void)
{
	char *input, *arg;
	int exit_status;

	while (1)
	{
		write_to_stdout("kings_shell$$> ");
		input = readUserInput();

		if (input != NULL)
		{
			if (_strcmp(input, "exit") == 0)
			{
				free(input);
				write_to_stdout("Exiting kings_shell$$\n");
				exit(0);
			}
			else if (_strncmp(input, "exit", 4) == 0)
			{
				arg = _strtok(input + 4, " ");
				exit_status = (arg != NULL) ? _atoi(arg) : 0;
				write_to_stdout("Exit status: ");
				exit(exit_status);
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
