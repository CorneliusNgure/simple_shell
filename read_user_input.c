#include "simple_shell.h"

/**
 * readUserInput - reads the input command.
 *
 * Return: the user input.
 */

char *readUserInput()
{
	char input[1024];
	char *userInput;

	if (fgets(input, sizeof(input), stdin) == NULL)
	return (NULL);

	if (strlen(input) > 0 && input[strlen(input) - 1] == '\n')
	{
		input[strlen(input) - 1] = '\0';
	}

	userInput = strdup(input);
	if (userInput == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	return (userInput);
}
