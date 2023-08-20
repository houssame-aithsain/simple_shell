#include "simple_shell.h"

void __exit(t_container *src)
{
	if (!_strcmp(src->path, "exit"))
	{
		int exit_code;

		if (src->arg[1])
		{
			exit_code = _atoi(src->arg[1]);
			free(src->line);
			free(src->path);
			if (src->is_fd)
				free(src->fdLine);
			if (!src->is_fd)
				free(src->mainLine);
			free(src->cmd_path);
			_free(src->splitedLines, NULL, 1);
			_free(src->mc_arg, NULL, 1);
			_free(src->alias.name, NULL, 1);
			_free(src->alias.value, NULL, 1);
			_free(src->arg, NULL, 1);
			_free(src->env, NULL, 1);
			exit(exit_code);
		}
		else
		{
			free(src->line);
			free(src->path);
			if (src->is_fd)
				free(src->fdLine);
			if (!src->is_fd)
				free(src->mainLine);
			free(src->cmd_path);
			_free(src->splitedLines, NULL, 1);
			_free(src->mc_arg, NULL, 1);
			_free(src->alias.name, NULL, 1);
			_free(src->alias.value, NULL, 1);
			_free(src->arg, NULL, 1);
			_free(src->env, NULL, 1);
			exit(0);
		}
	}
}

int PrintAliasName(t_container *src, int flag, int i)
{
	int len = 0;

	if (!flag)
	{
		if (src->arg[0] && !src->arg[1])
		{
			while (src->alias.name && src->alias.name[i])
			{
				write(1, src->alias.name[i], _strlen(src->alias.name[i]));
				write(1, "='", 2);
				write(1, src->alias.value[i], _strlen(src->alias.value[i]));
				write(1, "'\n", 2);
				i++;
			}
			return (0);
		}
		return (1);
	}
	while (src->alias.name && src->alias.name[len])
	{
		if (!_strcmp(src->alias.name[len], src->arg[i]))
		{
			write(1, src->alias.name[len], _strlen(src->alias.name[len]));
			write(1, "='", 2);
			write(1, src->alias.value[len], _strlen(src->alias.value[len]));
			write(1, "'\n", 2);
			break;
		}
		len++;
	}
	return (len);
}

int _alias(t_container *src)
{
	int i = 0, len;

	if (!_strcmp(src->path, "alias"))
	{
		if (!PrintAliasName(src, 0, i))
			return (1);
		while (src->arg && src->arg[i])
		{
			if (src->arg[i][0] == '=')
			{
				_alias_error(src, 0, i, 0);
				return (22);
			}
			i++;
		}
		i = 1;
		while (src->arg[i])
		{
			if (!__is_alias_of_x(src->arg[i]))
				create_new_alias(src->arg[i], src);
			else
			{
				len = PrintAliasName(src, 1, i);
				_alias_error(src, len, i, 1);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int _cd(t_container *src)
{
	char *HOME;

	if (!_strcmp(src->path, "cd"))
	{
		if (src->arg[1])
		{
			if (!_strcmp(src->arg[1], "-"))
			{
				if (chdir(src->last_p))
					perror("chdir");
				write(1, src->last_p, _strlen(src->last_p));
				write(1, "\n", 1);
			}
			else
			{
				if (chdir(src->arg[1]))
					_cd_error(src);
			}
		}
		if (!src->arg[1])
		{
			if (chdir(HOME = get_HOME_dir()))
				perror("chdir");
			free(HOME);
		}
		_strcpy(src->last_p, src->current_p);
		if (!getcwd(src->current_p, sizeof(src->current_p)))
			perror("getcwd");
		_create_new_var("PWD", src->current_p, src);
		return (3);
	}
	return (0);
}

int builtins(t_container *src)
{
	__exit(src);
	if (_strcmp(src->path, src->arg[0]))
		return (0);
	if (_unsetenv(src) || _cd(src) || _env(src) || _alias(src) || _setenv(src))
		return (1);
	return (0);
}