#include "simple_shell.h"

/**
 * _strcat - concatenates two strings.
 * @dest: string to be concatenated.
 * @src: string to be concatenated.
 *
 * Return: dest.
 */

char *_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strdup - mimics the strdup function.
 * @src: the string to be duplicated.
 *
 * Return: the duplicated string.
 */

char *_strdup(const char *src)
{
	char *dest = (char *)malloc(_strlen(src));

	if (dest == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	_strncpy(dest, src, _strlen(src) + 1);

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

char *_strncpy(char *dest, const char *src, int n)
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

int _strlen(const char *s)
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
	char *userInput = custom_getline();

	if (userInput != NULL && _strlen(userInput) > 0)
	{
		if (userInput[_strlen(userInput) - 1] == '\n')
		{
			userInput[_strlen(userInput) - 1] = '\0';
		}
	}

	return (userInput);
}
