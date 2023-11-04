#include "simple_shell.h"

/**
 * write_to_stdout - prints to the standard output.
 * @outputText: message to be printed.
 *
 * Return: void.
 */

void write_to_stdout(const char *outputText)
{
	size_t output_length = strlen(outputText);
	size_t bytes_written = write(STDOUT_FILENO, outputText, output_length);

	if (bytes_written = -1)
		perror("Write error");
}
