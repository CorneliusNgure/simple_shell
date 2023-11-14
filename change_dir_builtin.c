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
		return (str);
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
	return (str);
}
