#include "simple_shell.h"

/**
 * _strncmp - compares two strings up to n no. of characters.
 * @s1: the first string.
 * @s2: the second string.
 * @n: the maximum number of characters to compare.
 * Return:
 *   - 0 if the strings are equal,
 *   - a negative value if s1 is less than s2,
 *   - a positive value if s1 is greater than s2.
 */

int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; ++i)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return (s1[i] - s2[i]);
	}

	return (0);
}

/**
 * _isdigit - checks for a digit (0 through 9)
 *
 * @c: digit to be checked.
 *
 * Return: 1 if c is a digit and 0 otherwise.
 */

int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/**
 * _strcpy - Copies a string from source to destination.
 * @dest: The destination buffer.
 * @src: The source string to be copied.
 * Return: A pointer to the destination buffer.
 */

char *_strcpy(char *dest, const char *src)
{
	char *dest_start = dest;

	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = '\0';

	return (dest_start);
}

/**
 * run_user_command - executes the user input command.
 * @input: the user command.
 */
void run_user_command(char *input)
{
    char **commands, *token, *command;
    const char *separator = ";";
    int len, i = 0, j;

    if (input == NULL)
        return;

    commands = malloc(BUFFER_SIZE * sizeof(char *));
    if (commands == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = _strtok(input, separator);

    while (token != NULL)
    {
        commands[i] = token;
        i++;
        token = _strtok(NULL, separator);
    }

    commands[i] = NULL;

    for (j = 0; j < i; j++)
    {
        *command = commands[j];

        while (*command == ' ')
            command++;

        len = _strlen(command);
        while (len > 0 && command[len - 1] == ' ')
            command[--len] = '\0';

        if (_strlen(command) > 0)
        {
            execute_single_command(command);
        }
    }

    free(commands);
    free(input);
}


/**
 * execute_single_command - executes a single command.
 * @args: the arguments passed to the command.
 */
void execute_single_command(char **args)
{
    int status, exit_status;
    pid_t pid;
    char error_msg[] = "Command exited with error: ";
    char *full_error_msg, *exec_path;

    pid = fork();
    if (pid == -1)
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        exec_path = get_env_path(args[0]);
        if (exec_path != NULL)
        {
            if (execve(exec_path, args, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            full_error_msg = malloc(_strlen(error_msg) + _strlen(args[0]) + 1);
            if (full_error_msg == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            _strcpy(full_error_msg, error_msg);
            _strcat(full_error_msg, args[0]);
            write_to_stdout(full_error_msg);

            free(full_error_msg);

            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);

        if (WIFEXITED(status))
        {
            exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
            {
                write_to_stdout("Command exited with status: ");
                write_to_stdout(_itoa(exit_status));
                write_to_stdout("\n");
            }
        }
    }
}
