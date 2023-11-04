#include "simple_shell.h"

/**
 * readUserInput - reads the input command.
 *
 * Return: the user input.
 */

char *readUserInput()
{
	char input[1024];
	size_t input_length = strlen(input);
	char *userInput;

	if (fgets(input, sizeof(input), stdin) == NULL)
		return (NULL);

	if (input_length > 0 && input[input_length - 1] == '\n')
	{
		input[input_length - 1] = '\0';
	}

	userInput = strdup(input);
	if (userInput == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	return (userInput);
}
