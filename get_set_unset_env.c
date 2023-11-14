#include "simple_shell.h"

/**
 * _strcspn - custom implementation of strcspn.
 * @s: the string to search.
 * @reject: the characters to reject.
 *
 * Return: length of initial segment not containing any character in reject.
 */

size_t _strcspn(char *s, char *reject)
{
	char *p = s;

	while (*p != '\0' && !_strchr(reject, *p))
	{
		p++;
	}
	return (p - s);
}

/**
 * _getenv - custom implementation of getenv function.
 * @name: the name of the environment variable.
 * Return: the value of the environment variable or NULL if not found.
 */
char *_getenv(char *name)
{
	extern char **environ;
	int i, len = _strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
	}

	return (NULL);
}

/**
 * _setenv - set an environment variable
 * @name: the name of the variable
 * @value: the value to set
 * @overwrite: flag to indicate whether to overwrite an existing variable
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(char *name, char *value, int overwrite)
{
	char *env_var, *new_env_var;

	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);

	env_var = _getenv(name);

	if (env_var != NULL && !overwrite)
		return (0);

	new_env_var = malloc(_strlen(name) + _strlen(value) + 2);
	if (new_env_var == NULL)
	{
		perror("malloc");
		return (-1);
	}

	_strcpy(new_env_var, name);
	_strcat(new_env_var, "=");
	_strcat(new_env_var, value);

	return (0);
}

/**
 * _unsetenv - unset an environment variable
 * @name: the name of the variable to unset
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);

	if (_unsetenv(name) != 0)
	{
		perror("unsetenv");
		return (-1);
	}

	return (0);
}

/**
 * exit_shell_with_status - exits shell with the specified status.
 * @status: the status variable.
 */

void exit_shell_with_status(int status)
{
	write_to_stdout("Exiting kings_shell$$...\n");
	exit(status);
}
