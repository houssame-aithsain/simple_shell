#include "simple_shell.h"

int TDPCounter(char **arr)
{
	int i = 0;

	while (arr && arr[i])
		i++;
	return (i);
}

int __is_alias_of_x(char *var)
{
    int i = 0;

    while (var && var[i])
    {
        if (var[i] == '=')
            return (0);
        i++;
    }
    return (-88);
}

void __IfAliasIsEmpty(char *str, t_container *src)
{
    src->alias.name = malloc(sizeof(char *) * 2);
    src->alias.value = malloc(sizeof(char *) * 2);
    src->alias.name[0] = get_name_or_value(str, NAME);
    src->alias.value[0] = get_name_or_value(str, VALUE);
    src->alias.name[1] = NULL;
    src->alias.value[1] = NULL;
}

void __new_alias_table(t_container *src, char **name, char **value)
{
    _free(src->alias.name, NULL, 1);
    _free(src->alias.value, NULL, 1);
    src->alias.name = name;
    src->alias.value = value;
}
/*
alias && alias n='ls -la' && alias n && alias n='echo hello world' && alias n ; alias
*/