#include "simple_shell.h"

/**
 * _NPC_remover - Removes non-printable characters from command arguments
 * @src: Shell container
 *
 * Removes non-printable characters from arguments in @src.
 */
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

/**
 * __var_init - Initializes the shell container with default values
 * @src: Shell container
 * @argc: Number of command-line arguments
 * @argv: Command-line arguments array
 *
 * Initializes fields in @src with default values.
 */
void __var_init(t_container *src, int argc, char **argv)
{
	char *old;

	(void)argc;
	src->is_fd = 0;
	src->exit_status = 0;
	src->cmd_counter = 0;
	src->p_name = argv[0];
	src->alias.name = NULL;
	src->alias.value = NULL;
	if (!getcwd(src->PWD, sizeof(src->PWD)))
		perror("getcwd");
	old = get_OLDPWD_dir();
	if (old)
		_strcpy(src->OLDPWD, old);
	else
		_strcpy(src->OLDPWD, src->PWD);
	free(old);
	set_env(src);
}


/**
 * __main_free - Frees memory allocated for shell container resources
 * @src: Shell container
 * @flag: Resource deallocation flag (FD for file descriptor mode)
 *
 * Deallocates memory for resources in @src based on @flag.
 */
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
		_free(src->and_cmds, NULL, 1);
		return;
	}
	free(src->mainLine);
	_free(src->arg, NULL, 1);
	_free(src->env, NULL, 1);
	_free(src->alias.name, NULL, 1);
	_free(src->alias.value, NULL, 1);
}

/**
 * __fd_status - Checks if a filename contains a path separator
 * @filename: Filename to check
 *
 * Checks if @filename contains a path separator (/).
 * Return: 0 or -21.
 */
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


/**
 * __new_line_sanitizer - Removes newline characters from a string
 * @str: String to sanitize
 *
 * Replaces newlines in @str with null terminators.
 */
void __new_line_sanitizer(char *str)
{
	int i = -1;

	while (str && str[++i])
	{
		if (str[i] == '\n')
			str[i] = 0;
	}
}
