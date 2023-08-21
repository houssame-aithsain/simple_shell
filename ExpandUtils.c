#include "simple_shell.h"


/**
 * get_exit_status - Converts the exit status to a string.
 * @exit_status: The exit status to be converted.
 * Return: The exit status as a string.
 */
char *get_exit_status(int exit_status)
{
	return (_itoa(exit_status));
}

/**
 * get_str_format - Extracts a string format from the input string.
 * @str: Input string.
 * Return: Extracted string format.
 */
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

/**
 * get_ps_id - Retrieves the process ID as a string.
 * Return: The process ID as a string.
 */
char *get_ps_id()
{
	return (_itoa(getpid()));
}

/**
 * get_var_value - Retrieves the value of a variable from the environment.
 * @str: Variable name.
 * @env: Environment array.
 * Return: Value of the variable or special character.
 */
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

/**
 * SortStrType - Expands variables, process ID
 * exit status, and strings in a string.
 * @str: Input string.
 * @src: Container holding command and argument data.
 * Return: Expanded string.
 */
char *SortStrType(char *str, t_container *src)
{
	int i = -1;
	char *value;

	value = malloc(2);
	value[0] = 0;
	while (str && str[++i])
	{
		if (str[i] == '$' && (str[i + 1] == '=' || !str[i + 1]))
			value = _strjoin(value, "$");
		else if (str[i] == '$' && str[i + 1] && str[i + 1] != '$' && str[i + 1] != '?')
			value = __var(str, value, &i, src);
		else if (str[i] == '$' && str[i + 1] == '$')
			value = __ps_id(value, &i);
		else if (str[i] == '$' && str[i + 1] == '?')
			value = __exit_status(value, &i, src);
		else if (str[i] && str[i] != '$')
			value = __string(str, value, &i);
	}
	free(str);
	return (value);
}
