#include "simple_shell.h"

/**
 * _strcspn - custom implementation of strcspn.
 * @s: the string to search.
 * @reject: the characters to reject.
 *
 * Return: the length of the initial segment not containing any character in reject.
 */

size_t _strcspn(const char *s, const char *reject)
{
    const char *p = s;
    while (*p != '\0' && !_strchr(reject, *p))
    {
        p++;
    }
    return (p - s);
}

/**
 * custom_getenv - gets the value of an environment variable.
 * @name: name of the environment variable.
 *
 * Return: value of the environment variable.
 */
char *_getenv(const char *name)
{
	char **environ;
	int i;
	const char *var;
	size_t len;

	for (i = 0; environ[i] != NULL; i++)
	{
		*var = environ[i];
		len = strcspn(var, "=");

	if (_strncmp(var, name, len) == 0 && var[len] == '=')
		return (var + len + 1);
	}

	return (NULL);
}

/**
 * custom_setenv - sets the value of an environment variable.
 * @name: name of the environment variable.
 * @value: value to set.
 * @overwrite: flag to indicate whether to overwrite if the variable already exists.
 *
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    char **environ;
    char **new_environ;
    int env_count, i, j;
    size_t len;
    const char *var;

    for (env_count = 0; environ[env_count] != NULL; env_count++);

	new_environ = malloc((env_count + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		perror("malloc");
		return (-1);
	}

	for (i = 0; i < env_count; i++)
	{
		new_environ[i] = _strdup(environ[i]);
		if (new_environ[i] == NULL)
		{
			perror("malloc");
			for (j = 0; j < i; j++)
				free(new_environ[j]);
			free(new_environ);
			return (-1);
		}
	}

	for (i = 0; i < env_count; i++)
	{
		*var = new_environ[i];
		len = _strcspn(var, "=");

	if (_strncmp(var, name, len) == 0 && var[len] == '=')
	{
		if (!overwrite)
		{
			free(new_environ[env_count]);
			free(new_environ);
			return (0);
		}

		free(new_environ[i]);
		new_environ[i] = malloc(len + _strlen(value) + 2);
		if (new_environ[i] == NULL)
		{
			perror("malloc");
			for (j = 0; j < i; j++)
				free(new_environ[j]);
			free(new_environ);
			return (-1);
		}

		snprintf(new_environ[i], len + _strlen(value) + 2, "%s=%s", name, value);

		free(new_environ[env_count]);
		free(new_environ);
		return (0);
	}
	
	new_environ[env_count] = malloc(_strlen(name) + _strlen(value) + 2);
	if (new_environ[env_count] == NULL)
	{
		perror("malloc");
		for (i = 0; i <= env_count; i++)
			free(new_environ[i]);
		free(new_environ);
		return (-1);
	}

	snprintf(new_environ[env_count], _strlen(name) + _strlen(value) + 2, "%s=%s", name, value);

	new_environ[env_count + 1] = NULL;

	free(environ);
	environ = new_environ;

	return (0);
}

/**
 * _unsetenv - unsets an environment variable.
 * @name: name of the environment variable.
 *
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name)
{
    char **environ, new_environ;
    int env_count, i, j, k;
    const char *var;
    size_t len;

	for (env_count = 0; environ[env_count] != NULL; env_count++)
	{
		for (i = 0; i < env_count; i++)
		{
			*var = environ[i];
			len = strcspn(var, "=");

			if (_strncmp(var, name, len) == 0 && var[len] == '=')
			{
				free(environ[i]);

				for (j = i; j < env_count; j++)
					environ[j] = environ[j + 1];

				**new_environ = malloc(env_count * sizeof(char *));
				
				if (new_environ == NULL)
				{
					perror("malloc");
					return (-1);
				}
				
				for (j = 0; j < env_count - 1; j++)
				{
					new_environ[j] = _strdup(environ[j]);
					if (new_environ[j] == NULL)
					{
						perror("malloc");

						for (k = 0; k < j; k++)
							free(new_environ[k]);
						free(new_environ);
						return (-1);
					}
				}
				
				new_environ[env_count - 1] = NULL;
				free(environ);
				environ = new_environ;

				return (0);
			}
		}

		return (0);
}


/**
 * exit_shell_with_status - Exit the shell with a specified status.
 * @status: The exit status code.
 *
 */

void exit_shell_with_status(int status)
{
    write_to_stdout("Exiting kings_shell$$...\n");
    exit(status);
}
