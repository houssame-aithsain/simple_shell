#include "simple_shell.h"

char *__var(char *str, char *value, int *i, t_container *src)
{
	char *tmp;

	tmp = get_var_value(*i + 1 + str, src->env);
	value = _strjoin(value, tmp);
	*(i) += GetVarLent(*i + 1 + str);
	free(tmp);
	return (value);
}

char *__ps_id(char *value, int *i)
{
	char *tmp;

	tmp = get_ps_id();
	value = _strjoin(value, tmp);
	free(tmp);
	*(i) += 1;
	return (value);
}

char *__exit_status(char *value, int *i, t_container *src)
{
	char *tmp;

	tmp = get_exit_status(src->exit_status);
	value = _strjoin(value, tmp);
	free(tmp);
	*(i) += 1;
	return (value);
}

char *__string(char *str, char *value, int *i)
{
	char *tmp;

	tmp = get_str_format(*(i) + str);
	value = _strjoin(value, tmp);
	free(tmp);
	*(i) += GetVarLent_str(*(i) + 1 + str);
	return (value);
}

void _expand(t_container *src)
{
	int i = 0, len;
	char **tmp;

	while (src->arg && src->arg[i])
		i++;
	src->arg_lent = i;
	i = -1;
	while (src->arg && src->arg[++i])
	{
		len = -1;
		while (src->arg[i][++len])
		{
			if (src->arg[i][len] == '$')
				src->arg[i] = SortStrType(src->arg[i], src);
		}
	}
	i = 0;
	len = 0;
	tmp = malloc(sizeof(char *) * TDPCounter(src->arg) + 10);
	while (src->arg && src->arg[i])
	{
		if (src->arg[i][0] == 5 && !src->arg[i][1])
			i++;
		if (!src->arg[i])
			break;
		tmp[len++] = _strdup(src->arg[i++]);
	}
	tmp[len] = NULL;
	_free(src->arg, NULL, 1);
	src->arg = tmp;
	_NPC_remover(src);
	if (!src->arg[0] || !src->arg[0][0])
		src->is_empty = EMPTY;
}
/*
echo $$$PATH$$hello,world$$
alias ll='echo $PATH'
alias ll='echo $PATH $PWD $SDFSDF'
*/