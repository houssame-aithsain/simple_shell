#include "simple_shell.h"

void __var_init(t_container *src, int argc, char **argv)
{
	(void)argc;
	src->cmd_counter = 0;
	src->p_name = argv[0];
	src->alias.name = NULL;
	src->alias.value = NULL;
	if (!getcwd(src->current_p, sizeof(src->current_p)))
		perror("getcwd");
	_strcpy(src->last_p, src->current_p);
}

void __main_free(t_container *src)
{
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

