#include "simple_shell.h"

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
			if (str[i] != '\'')
				buffer[i] = str[i];
		}
		buffer[i] = 0;
	}
	else
	{
		i = 0;
		while (str && str[len] != '=')
			len++;
		len++;
		for (; str && str[len]; len++)
		{
			if (str[len] != '\'')
				buffer[i++] = str[len];
		}
		buffer[i] = 0;
		if (!buffer[0])
			_strcpy(buffer, "");
	}
	return (buffer);
}

void __create_new_alias_name(char *str, t_container *src)
{
	int len = 0, true = 1;
    char **name, **value, *tmp;

	name = malloc(sizeof(char *) * (TwoDPointerCounter(src->alias.name) + 2));
	value = malloc(sizeof(char *) * (TwoDPointerCounter(src->alias.value) + 2));
	while (src->alias.name[len])
	{
		name[len] = malloc(_strlen(src->alias.name[len]) + 2);
		value[len] = malloc(_strlen(src->alias.value[len]) + _strlen(str));
		_strcpy(name[len], src->alias.name[len]);
		if (_strcmp(src->alias.name[len], (tmp = get_name_or_value(str, NAME))))
		{
			_strcpy(value[len], src->alias.value[len]);
			free(tmp);
		}
		else
		{
			free(tmp);
			_strcpy(value[len], (tmp = get_name_or_value(str, VALUE)));
			free(tmp);
			true = 0;
		}
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

void create_new_alias(char *str, t_container *src)
{
	if (!TwoDPointerCounter(src->alias.name))
		__IfAliasIsEmpty(str, src);
	else
		__create_new_alias_name(str, src);
}

/*ls; ls -la; lss || echo startOR; echo startAND && lss; alias n============================; alias n; alias; alias n=ls; alias n='echo hello world sdfsdf sdfsd sdfsdf sdfsdf sdf98484 4'; alias n; dfgd fg df g dfgdfg ; env ; setenv h hellow ; env ; unset hellow;*/