#include "simple_shell.h"

/**
 * CheckToCreateNewVar - Checks and creates a new environment variable.
 * @src: Container holding command and argument data.
 */
void CheckToCreateNewVar(t_container *src)
{
	char *name, *value;

	if (src->arg[1])
	{
		if (src->arg[2])
		{
			name = _strdup(src->arg[1]);
			value = _strdup(src->arg[2]);
		}
		else
			return;
	}
	else
		return;
	if (_var_check(name, value))
	{
		errno = EINVAL;
		perror("setenv");
	}
	_create_new_var(name, value, src);
	free(name);
	free(value);
}

/**
 * _var_unset - Unsets an environment variable.
 * @src: Container holding command and argument data.
 * Return: Result code based on operation success.
 */
int _var_unset(t_container *src)
{
	int i = 0;

	for (; src->env[i]; i++)
	{
		if (!_strncmp(src->arg[1], src->env[i], _strlen(src->arg[1])))
			break;
	}
	if (!src->env[i])
		return (-11);
	free(src->env[i++]);
	while (src->env[i])
	{
		src->env[i - 1] = malloc(_strlen(src->env[i]) + 1);
		_strcpy(src->env[i - 1], src->env[i]);
		free(src->env[i]);
		i++;
	}
	src->env[i - 1] = NULL;
	return (0);
}

/**
 * _unsetenv - Handles the 'unsetenv' command.
 * @src: Container holding command and argument data.
 * Return: Result code based on operation success.
 */
int _unsetenv(t_container *src)
{
	if (!_strcmp(src->path, src->arg[0]))
	{
		if (!_strcmp(src->path, "unsetenv"))
		{
			if (src->arg[1])
			{
				if (_var_unset(src))
				{
					errno = EINVAL;
					perror("unsetenv");
				}
			}
			return (2);
		}
	}
	return (0);
}


/**
 * _setenv - Handles the 'setenv' command.
 * @src: Container holding command and argument data.
 * Return: Result code based on operation success.
 */
int _setenv(t_container *src)
{
	if (!_strcmp(src->path, src->arg[0]))
	{
		if (!_strcmp(src->path, "setenv"))
		{
			CheckToCreateNewVar(src);
			return (5);
		}
	}
	return (0);
}

/**
 * _env - Handles the 'env' command.
 * @src: Container holding command and argument data.
 * Return: Result code based on operation success.
 */
int _env(t_container *src)
{
	int i = 0;

	if (!_strcmp(src->arg[0], "env"))
	{
		if (!src->env[i])
			return (0);
		for (; src->env[i]; i++)
		{
			write(1, src->env[i], _strlen(src->env[i]));
			write(1, "\n", 1);
		}
		return (4);
	}
	return (0);
}
