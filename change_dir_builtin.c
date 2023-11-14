#include "simple_shell.h"

/**
 * cd_built_in - changes the current working directory.
 * @args: the arguments passed to the cd command.
 */

void cd_built_in(char **args)
{
	char *new_dir, *current_dir;

	if (args[1] == NULL || _strcmp(args[1], "~") == 0)
		new_dir = _getenv("HOME");

	else if (_strcmp(args[1], "-") == 0)
	{
		new_dir = _getenv("OLDPWD");
	}
	else
		new_dir = args[1];

	if (new_dir == NULL)
		perror("cd");

	else
	{
		current_dir = getcwd(NULL, 0);
		if (current_dir == NULL)
		{
			perror("getcwd");
			return;
		}

		if (chdir(new_dir) == 0)
		{
			_setenv("OLDPWD", current_dir, 1);
			_setenv("PWD", getcwd(NULL, 0), 1);
		}
	else
		perror("cd");

	free(current_dir);
	}
}

/**
 * get_env_path - gets the PATH.
 * @command: user input command.
 *
 * Return: pointer to PATH.
 */

char *get_env_path(char *command)
{
	char *path = _getenv("PATH");
	char *token, *full_path;
	char delimiter[] = ":";

	token = _strtok(path, delimiter);

	while (token != NULL)
	{
		full_path = malloc(_strlen(token) + _strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		_strcpy(full_path, token);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}

		free(full_path);
		token = _strtok(NULL, delimiter);
	}
	return (NULL);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer to convert.
 * @str: The buffer to store the resulting string.
 * @base: The base for conversion.
 * Return: A pointer to the resulting string.
 */
char *_itoa(int num, char *str, int base)
{
	int i = 0, start, end, remainder;
	int isNegative = 0;
	char temp;

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	if (num < 0 && base == 10)
	{
		isNegative = 1;
		num = -num;
	}

	while (num != 0)
	{
		remainder = num % base;
		str[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
		num = num / base;
	}

	if (isNegative && base == 10)
	{
		str[i++] = '-';
	}

	str[i] = '\0';

	start = 0;
	end = i - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}

	return str;
}
