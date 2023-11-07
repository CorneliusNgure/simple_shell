#include "simple_shell.h"

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
