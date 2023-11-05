#include "simple_shell.h"

/**
 * _strdup - mimics the strdup function.
 * @src: the string to be duplicated.
 *
 * Return: the duplicated string.
 */

char _strdup(char *src)
{
	char *dest = (char *)malloc(_strlen(src));

	if (src == NULL)
		return (NULL);

	if (dest == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	_strncpy(dest, src);

	return (dest);
}



/**
 * _strncpy - copies a string to another.
 *
 * @dest: the string to be copied to.
 * @src: the string to be copied from.
 * @n: the exact number of bytes to be copied.
 *
 * Return: pointer to the copied string (dest).
 */

char *_strncpy(char *dest, char *src, int n)
{
	int count = 0;

	while (count < n && src[count] != '\0')
	{
		dest[count] = src[count];
		count++;
	}

	while (count < n)
	{
		dest[count] = '\0';
		count++;
	}

	return (dest);
}

/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length
 */

int _strlen(char *s)
{
	int string_length = 0;

	while (*s != '\0')
	{
		string_length++;
		s++;
	}

	return (string_length);
}

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

	if (_strlen(input) > 0 && input[_strlen(input) - 1] == '\n')
	{
		input[_strlen(input) - 1] = '\0';
	}

	userInput = _strdup(input);
	if (userInput == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	return (userInput);
}
