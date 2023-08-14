#include "simple_shell.h"

int if_var_exist(char *name, char *value, t_container *src)
{
	int p = 0, cp, i;
	char *tmp;

	for (; src->env[p]; p++)
	{
		if (!_strncmp(name, src->env[p], _strlen(name)))
			break;
	}
	if (!src->env[p])
		return (-10);
	i = -1;
	tmp = malloc(_strlen(name) + _strlen(value) + 3);
	_strcpy(tmp, name);
	cp = _strlen(tmp);
	tmp[cp++] = '=';
	while (value[++i])
		tmp[cp++] = value[i];
	tmp[cp] = 0;
	free(src->env[p]);
	src->env[p] = tmp;
	return (0);
}

int _var_check(char *name, char *value)
{
	int i = 0;

	if (!name || !value)
		return (-3);
	for (; name[i]; i++)
	{
		if (name[i] == '=')
			return (-2);
	}
	return (0);
}

int _create_new_var(char *name, char *value, t_container *src)
{
	int i = -1, cp, len = 0;
	char **env;

	if (!if_var_exist(name, value, src))
		return (0);
	while (src->env[len])
		len++;
	env = malloc(sizeof(char *) * (len + 2));
	len = 0;
	while (src->env[len])
	{
		if (!src->env[len])
			break;
		env[len] = malloc(_strlen(src->env[len]) + 2);
		_strcpy(env[len], src->env[len]);
		len++;
	}
	env[len] = malloc(_strlen(name) + _strlen(value) + 3);
	_strcpy(env[len], name);
	cp = _strlen(env[len]);
	env[len][cp++] = '=';
	while (value[++i])
		env[len][cp++] = value[i];
	env[len][cp] = 0;
	env[len + 1] = NULL;
	_free(src->env, NULL, 1);
	src->env = env;
	return (0);
}

void set_env(t_container *src)
{
	int len = 0;

	while (environ[len])
		len++;
	src->env = malloc(sizeof(char *) * (len + 2));
	len = -1;
	while (environ[++len])
	{
		src->env[len] = malloc(_strlen(environ[len]) + 1);
		_strcpy(src->env[len], environ[len]);
	}
	src->env[len] = NULL;
}