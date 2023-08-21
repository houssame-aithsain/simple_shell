#include "simple_shell.h"

/**
 * AliasLineEnhancer - Expands command with alias substitution.
 * @src: Container holding alias data and arguments.
 * Return: 0 on success, -15 if no alias found.
 */
int AliasLineEnhancer(t_container *src)
{
	int i = 0, len = 0;
	char **args, **tmp;

	if (!src->alias.name)
		return (-15);
	while (src->alias.name[i])
	{
		if (!_strcmp(src->alias.name[i], src->arg[0]))
			break;
		i++;
	}
	if (!src->alias.name[i] || !_strcmp(src->alias.value[i], ""))
		return (-15);
	args = malloc(sizeof(char *) * 100);
	tmp = strtow(src->alias.value[i], ' ');
	i = 0;
	while (tmp && tmp[i])
		args[len++] = _strdup(tmp[i++]);
	i = 1;
	while (src->arg && src->arg[i])
		args[len++] = _strdup(src->arg[i++]);
	args[len] = NULL;
	_free(tmp, NULL, 1);
	_free(src->arg, NULL, 1);
	src->arg = NULL;
	src->arg = args;
	free(src->path);
	src->path = _strdup(src->arg[0]);
	return (0);
}

/**
 * if_valide - Checks if command is valid for alias expansion.
 * @args: Arguments to check.
 * Return: 0 if valid, -20 otherwise.
 */
int if_valide(char **args)
{
	int i = 0, s_quote = 0;

	while (args && args[i])
	{
		if (if_s_quote(args[i]))
			s_quote++;
		i++;
	}
	if (!_strcmp("alias", args[0]) && s_quote)
		return (0);
	return (-20);
}

/**
 * if_s_quote - Checks if string has single quotes.
 * @arg: String to check.
 * Return: Count of single quotes found.
 */
int if_s_quote(char *arg)
{
	int i = 0, s_quote = 0;

	while (arg && arg[i])
	{
		if (arg[i] == '\'')
			s_quote++;
		i++;
	}
	return (s_quote);
}

/**
 * get_join_alias_args - Joins args with embedded quotes.
 * @args: Arguments to process.
 * Return: Processed arguments.
 */
char **get_join_alias_args(char **args)
{
	char **tmp;
	int i = -1, t = 0, count, tp;

	if (if_valide(args))
		return (args);
	tmp = malloc(sizeof(char *) * (TDPCounter(args) + 2));
	while (args && args[++i])
	{
		count = 0;
		if (!(if_s_quote(args[i]) % 2))
			tmp[t++] = _strdup(args[i]);
		else if (if_s_quote(args[i]))
		{
			tmp[t] = _strdup(args[i++]);
			tp = i - 1;
			while (args[++tp])
			{
				if (if_s_quote(args[tp]))
					break;
				count++;
			}
			tp = 0;
			while (tp <= count)
			{
				tmp[t] = __strjoin(tmp[t], args[i++]);
				tp++;
			}
			i--;
			t++;
		}
		if (!args[i])
			break;
	}
	if (tmp[t - 1][_strlen(tmp[t - 1]) - 1] == 32)
		tmp[t - 1][_strlen(tmp[t - 1]) - 1] = 0;
	tmp[t] = NULL;
	_free(args, NULL, 1);
	return (tmp);
}
