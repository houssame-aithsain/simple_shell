#include "simple_shell.h"

/**
 * _var_check - Check if a variable name is valid
 * @name: Name of the variable
 * @value: Value of the variable
 *
 * Checks if the variable name @name is valid and doesn't contain '='.
 * Return: 0 if valid, -2 if invalid.
 */
int _var_check(char *name, char *value)
{
	int i = 0;

	if (!name || !value)
		return (0);
	for (; name[i]; i++)
	{
		if (name[i] == '=')
			return (-2);
	}
	return (0);
}

/**
 * __is_exist - Check if a variable exists in the environment
 * @name: Name of the variable
 * @value: Value of the variable
 * @src: Shell container
 *
 * Checks if the variable @name exists in the environment
 * of the shell container @src.
 * Return: 0 if exists, -10 if not found.
 */
int __is_exist(char *name, char *value, t_container *src)
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

/**
 * _create_new_var - Create a new environment variable
 * @name: Name of the variable
 * @value: Value of the variable
 * @src: Shell container
 *
 * Creates a new environment variable with the given @name
 * and @value in the shell container @src.
 * Return: 0 on success.
 */
int _create_new_var(char *name, char *value, t_container *src)
{
	int i = -1, cp, len = 0;
	char **env;

	if (!name || !value)
		return (0);
	if (!__is_exist(name, value, src))
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

/**
 * set_env - Set up the initial environment in the shell container
 * @src: Shell container
 *
 * Sets up the initial environment in the shell container @src by
 * copying the environment variables.
 */
void set_env(t_container *src)
{
	int len = -1;

	src->env = malloc(sizeof(char *) * (TDPCounter(src->envarg) + 2));
	while (src->envarg[++len])
	{
		src->env[len] = malloc(_strlen(src->envarg[len]) + 1);
		_strcpy(src->env[len], src->envarg[len]);
	}
	src->env[len] = NULL;
}
