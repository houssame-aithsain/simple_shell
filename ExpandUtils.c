#include "simple_shell.h"

char *get_exit_status(int exit_status)
{
	return (ft_itoa(exit_status));
}

char *get_str_format(char *str)
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
	while (str && str[i] && str[i] != '$' && str[i] != '\'' && str[i] != '=')
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
	value = malloc(_strlen(str) + 1);
	value[0] = 5;
	value[1] = 0;
	free(tmp);
	return (value);
}

char *SortStrType(char *str, t_container *src)
{
	int i = -1;
	char *value;

	value = malloc(2);
	value[0] = 0;
	while (str && str[++i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != '$' && str[i + 1] != '?')
			value = __var(str, value, &i, src);
		else if (str[i] == '$' && str[i + 1] == '$')
			value = __ps_id(value, &i);
		else if (str[i] == '$' && str[i + 1] == '?')
			value = __exit_status(value, &i, src);
		else if (str[i] && str[i] != '$')
			value = __string(str, value, &i);
		else if (str[i] == '$' && !str[i + 1])
			value = _strjoin(value, "$");
	}
	free(str);
	return (value);
}
