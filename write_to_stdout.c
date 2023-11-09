#include "simple_shell.h"

/**
 * _strchr - function to locate a char in a string.
 * @s: pointer to the string.
 * @c: the char to be located.
 *
 * Return: pointer to c or NULL;
 */

const char *_strchr(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	return (NULL);
}

/**
 * is_delimiter - identifies delimeters in a string.
 * @c: the character to check.
 * @delim: the delimeter to look for.
 * Return: the delimeter.
 */

int is_delimiter(char c, const char *delim)
{
	while (*delim)
	{
		if (*delim == c)
		{
			return (1);
		}
		delim++;
	}
	return (0);
}

/**
 * _strtok - tokenizes a string.
 * @str: string to tokenize.
 * @delim: the delimeter.
 * Return: tokenized string.
 */

char *_strtok(char *str, const char *delim)
{
	static char *last_token;
	char *token;

	if (str)
	{
		last_token = str;
	}
	else if (!last_token)
		return (NULL);

	while (*last_token && is_delimiter(*last_token, delim))
	{
		last_token++;
	}

	if (*last_token == '\0')
	{
		last_token = NULL;
		return (NULL);
	}

	token = last_token;

	while (*last_token && !is_delimiter(*last_token, delim))
	{
		last_token++;
	}

	if (*last_token == '\0')
	{
		last_token = NULL;
	}
	else
	{
		*last_token = '\0';
		last_token++;
	}

	return (token);
}

/**
 * custom_getline - reads characters from the stdin into a static buffer.
 * Return: dynamically allocated string.
 */

char *custom_getline(void)
{
	static char buffer[BUFFER_SIZE];
	int i = 0;
	int c, length = 0;

	while (1)
	{
		if (i >= length)
		{
			length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (length == -1)
			{
				perror("read");
				exit(EXIT_FAILURE);
			}
			else if (length == 0)
				return (NULL);

			i = 0;
		}

		c = buffer[i++];
		if (c == '\n' || c == '\0')
		{
			buffer[--i] = '\0';

			return (_strdup(buffer));
		}
	}
}

/**
 * write_to_stdout - prints to the standard output.
 * @outputText: message to be printed.
 *
 * Return: void.
 */
void write_to_stdout(const char *outputText)
{
	int output_length = strlen(outputText);
	int bytes_written = write(STDOUT_FILENO, outputText, output_length);

	if (bytes_written == -1)
		perror("Write error");
}
