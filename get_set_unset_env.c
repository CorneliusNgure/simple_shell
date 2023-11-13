#include "simple_shell.h"

/**
 * _strcspn - custom implementation of strcspn.
 * @s: the string to search.
 * @reject: the characters to reject.
 *
 * Return: the length of the initial segment not containing any character in reject.
 */

size_t _strcspn(char *s, const char *reject)
{
    char *p = s;
    while (*p != '\0' && !_strchr(reject, *p))
    {
        p++;
    }
    return (p - s);
}

/**
 * _setenv - set an environment variable
 * @name: the name of the variable
 * @value: the value to set
 * @overwrite: flag to indicate whether to overwrite an existing variable
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char *env_var, new_env_var;

    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
        return (-1);

    env_var = getenv(name);

    if (env_var != NULL && !overwrite)
        return (0);

    new_env_var = malloc(strlen(name) + strlen(value) + 2);
    if (new_env_var == NULL)
    {
        perror("malloc");
        return (-1);
    }

    strcpy(new_env_var, name);
    strcat(new_env_var, "=");
    strcat(new_env_var, value);

    if (putenv(new_env_var) != 0)
    {
        perror("putenv");
        free(new_env_var);
        return (-1);
    }

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
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
        return (-1);

    if (unsetenv(name) != 0)
    {
        perror("unsetenv");
        return (-1);
    }

    return (0);
}

void exit_shell_with_status(int status)
{
    write_to_stdout("Exiting kings_shell$$...\n");
    exit(status);
}
