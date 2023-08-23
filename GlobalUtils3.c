#include "simple_shell.h"

/**
 * is_path - Checks if a given command includes a path.
 * @src: Container holding command and argument data.
 * Return: Result code based on the presence of a path in the command.
 */
int is_path(t_container *src)
{
	int i = -1;
	DIR *dir;

	while (src->arg[0] && src->arg[0][++i])
	{
		if (src->arg[0][i] == '/')
		{
			dir = opendir(src->arg[0]);
			if (dir)
			{
				closedir(dir);
				_cmd_not_found(src, 1);
				return (0);
			}
			else
				return (-8);
		}
	}
	return (-8);
}

/**
 * GetDIrPath - Get the value of the PATH environment variable
 * @path: Pointer to store the path value
 * @src: Pointer to the container struct
 *
 * Searches for the "PATH" variable in environment
 * and stores its value in 'path'.
 * Return: 'path' if found, else NULL.
 */
char *GetDIrPath(char **path, t_container *src)
{
	int i = 0;

	for (; src->env[i]; i++)
	{
		if (!_strncmp("PATH", src->env[i], 4))
		{
			*path = _strdup(src->env[i]);
			return (*path);
		}
	}
	*path = NULL;
	return (NULL);
}

/**
 * is_alpha - Check if a string consists only of digits
 * @str: The input string
 *
 * Return: 1 if the string is composed entirely of digits, else 0.
 */
int is_alpha(char *str)
{
	int i = 0;

	while (str && str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

/**
 * get_OLDPWD_dir - Retrieves the value of the OLDPWD environment variable
 *
 * Return: A pointer to the value of the OLDPWD environment variable,
 *         or NULL if it is not found.
 */
char *get_OLDPWD_dir(void)
{
	char *path;
	int i = 0;

	path = NULL;
	for (; environ[i]; i++)
	{
		if (!_strncmp("OLDPWD", environ[i], 6))
			path = _strdup(environ[i]);
	}
	if (!path)
		return (NULL);
	return (_strcpy(path, path + 7));
}
