#include "simple_shell.h"

int GetVarLent(char *str)
{
	int i = 0;

	while (str && str[i] &&str[i] != '$')
		i++;
	return (i);
}

char *get_exit_status(int exit_status)
{
	return (ft_itoa(exit_status));
}

char *get_the_word(char *str)
{
	int i = 0, cp = 0;
	char *tmp;

	tmp = malloc(_strlen(str) + 1);
	while (str[i] && str[i] != '$')
		tmp[cp++] = str[i++];
	tmp[cp] = 0;
	return (tmp);
}

char *get_ps_id()
{
	return (ft_itoa(getpid()));
}

char *get_var_value(char *str, char **env)
{
	int i = 0;
	char *value, *tmp;

	value = NULL;
	tmp = malloc(_strlen(str) + 1);
	while (str && str[i] && str[i] != '$')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	i = -1;
	while (env && env[++i])
	{
		if (!_strncmp(env[i], tmp, _strlen(tmp)))
		{
			value = _strdup(_strlen(tmp) + (1 + env[i]));
			free(tmp);
			return (value);
		}
	}
	value = _strdup("~");
	value[0] = 0;
	free(tmp);
	return (value);
}

char *Get_Value(char *str, char **env, int exit_status)
{
	int i = -1;
	char *value, *tmp;

	value = malloc(10000);
	if (!value)
		exit(8);
	value[0] = 0;
	while (str && str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '$' && str[i + 1] != '?')
		{
			tmp = get_var_value(i + 1 + str, env);
			value = _strjoin(value, tmp);
			i += GetVarLent(i + 1 + str);
			free(tmp);
		}
		else if (str[i] == '$' && str[i + 1] == '$')
		{
			tmp = get_ps_id();
			value = _strjoin(value, tmp);
			free(tmp);
			i++;
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			tmp = get_exit_status(exit_status);
			value = _strjoin(value, tmp);
			free(tmp);
			i++;	
		}
		else if (str[i] && str[i] != '$')
		{
			tmp = get_the_word(i + str);
			value = _strjoin(value, tmp);
			free(tmp);
			i += GetVarLent(i + 1 + str);
		}
		else if (str[i] == '$' && !str[i + 1])
			value = _strjoin(value, "$");
	}
	free(str);
	return (value);
}

void ReplaceVarbyItsValue(t_container *src)
{
	int i = -1, len;

	while (src->arg && src->arg[++i])
	{
		len = -1;
		while (src->arg[i][++len])
		{
			if (!_strncmp(len + src->arg[i], "$", 1))
				src->arg[i] = Get_Value(src->arg[i], src->env, src->exit_status);
		}
	}
}

/*
echo $$PATH$$$PATH
*/