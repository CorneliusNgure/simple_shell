#include "simple_shell.h"

/**
 * cd_built_in - changes the current working directory.
 * @args: the arguments passed to the cd command.
 */

void cd_built_in(char **args)
{
	char *new_dir, *current_dir;

	if (args[1] == NULL || _strcmp(args[1], "~") == 0)
		new_dir = getenv("HOME");

	else if (_strcmp(args[1], "-") == 0)
	{
		new_dir = getenv("OLDPWD");
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
