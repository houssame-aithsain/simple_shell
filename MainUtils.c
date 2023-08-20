#include "simple_shell.h"

void _NPC_remover(t_container *src)
{
	int i = -1, len, cp;
	char *tmp, **arr;

	while (src && src->arg[++i])
	{
		len = -1;
		cp = 0;
		tmp = malloc(_strlen(src->arg[i]) + 1);
		while (src->arg[i][++len])
		{
			if (src->arg[i][len] != 5)
				tmp[cp++] = src->arg[i][len];
		}
		tmp[cp] = 0;
		free(src->arg[i]);
		src->arg[i] = _strdup(tmp);
		free(tmp);
	}
	i = 0;
	len = 0;
	arr = malloc(sizeof(char *) * (src->arg_lent + 1));
	while (src->arg && src->arg[i])
	{
		if (src->arg[i][0])
		{
			arr[len] = _strdup(src->arg[i]);
			len++;
		}
		i++;
	}
	arr[len] = NULL;
	_free(src->arg, NULL, 1);
	src->arg = arr;
}

void __var_init(t_container *src, int argc, char **argv)
{
	(void)argc;
	src->is_fd = 0;
	src->exit_status = 0;
	src->cmd_counter = 0;
	src->p_name = argv[0];
	src->alias.name = NULL;
	src->alias.value = NULL;
	if (!getcwd(src->current_p, sizeof(src->current_p)))
		perror("getcwd");
	_strcpy(src->last_p, src->current_p);
	set_env(src);
}

void __main_free(t_container *src, int flag)
{
	if (flag == FD)
	{
		free(src->line);
		free(src->path);
		free(src->mainLine);
		free(src->cmd_path);
		_free(src->splitedLines, NULL, 1);
		_free(src->mc_arg, NULL, 1);
		_free(src->arg, NULL, 1);
		return;
	}
	free(src->mainLine);
	_free(src->arg, NULL, 1);
	_free(src->env, NULL, 1);
	_free(src->alias.name, NULL, 1);
	_free(src->alias.value, NULL, 1);
}

int __fd_status(char *filename)
{
	int i = 0;

	for (; filename && filename[i]; i++)
	{
		if (!_strncmp(i + filename, "/", 1))
			return (0);
	}
	return (-21);
}

void __new_line_sanitizer(char *str)
{
	int i = -1;

	while (str && str[++i])
	{
		if (str[i] == '\n')
			str[i] = 0;
	}
}
