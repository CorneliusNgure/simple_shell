#include "simple_shell.h"

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
		run_user_command(input);

		if (input == NULL)
			break;
	}

	free(input);

	return (0);
}
