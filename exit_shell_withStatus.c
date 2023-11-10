#include "simple_shell.h"

/**
 * exit_shell_with_status - Exit the shell with a specified status.
 * @status: The exit status code.
 *
 */

void exit_shell_with_status(int status)
{
    write_to_stdout("Exiting the shell...\n");
    exit(status);
}

