#include "simple_shell.h"

/**
 * get_name_or_value - Extracts name or value from string.
 * @str: Input string containing name=value format.
 * @flag: Flag indicating name or value extraction.
 * Return: Extracted name or value.
 */
char *get_name_or_value(char *str, int flag)
{
	char *buffer;
	int i = 0, len = 0;

	buffer = malloc(_strlen(str) + 3);
	if (flag == NAME)
	{
		for (; str && str[i]; i++)
		{
			if (str[i] == '=')
				break;
			if (str[i] != '\'' && str[i] != 5)
				buffer[i] = str[i];
		}
		buffer[i] = 0;
	}
	else
	{
		i = 0;
		while (str && str[len] != '=')
			len++;
		if (str[len] == '=')
			len++;
		if (len)
		{
			for (; str && str[len]; len++)
			{
				if (str[len] != '\'')
					buffer[i++] = str[len];
			}
		}
		buffer[i] = 0;
		if (!buffer[0])
			_strcpy(buffer, "");
	}
	return (buffer);
}

/**
 * __create_new_alias_name - Creates new alias with name substitution.
 * @str: Input string containing new alias.
 * @src: Container holding alias data.
 */
void __create_new_alias_name(char *str, t_container *src)
{
	int len = 0, true = 1;
	char **name, **value, *tmp;

	name = malloc(sizeof(char *) * (TDPCounter(src->alias.name) + 2));
	value = malloc(sizeof(char *) * (TDPCounter(src->alias.value) + 2));
	while (src->alias.name[len])
	{
		name[len] = malloc(_strlen(src->alias.name[len]) + 2);
		value[len] = malloc(_strlen(src->alias.value[len]) + _strlen(str));
		_strcpy(name[len], src->alias.name[len]);
		tmp = get_name_or_value(str, NAME);
		if (_strcmp(src->alias.name[len], tmp))
		{
			_strcpy(value[len], src->alias.value[len]);
			free(tmp);
			tmp = NULL;
		}
		else
		{
			free(tmp);
			tmp = get_name_or_value(str, VALUE);
			_strcpy(value[len], tmp);
			free(tmp);
			tmp = NULL;
			true = 0;
		}
		free(tmp);
		len++;
	}
	name[len] = NULL;
	value[len] = NULL;
	if (true)
	{
		name[len] = get_name_or_value(str, NAME);
		value[len] = get_name_or_value(str, VALUE);
		name[len + 1] = NULL;
		value[len + 1] = NULL;
	}
	__new_alias_table(src, name, value);
}

/**
 * create_new_alias - Creates new alias based on input string.
 * @str: Input string containing new alias.
 * @src: Container holding alias data.
 */
void create_new_alias(char *str, t_container *src)
{
	if (!TDPCounter(src->alias.name))
		__IfAliasIsEmpty(str, src);
	else
		__create_new_alias_name(str, src);
}
