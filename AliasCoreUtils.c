#include "simple_shell.h"

/**
 * TDPCounter - Counts the elements in a NULL-terminated array.
 * @arr: Input array of strings.
 * Return: Number of elements in the array.
 */
int TDPCounter(char **arr)
{
	int i = 0;

	while (arr && arr[i])
		i++;
	return (i);
}

/**
 * __is_alias_of_x - Checks if input string is an alias.
 * @var: Input string to check.
 * Return: Return code indicating if the string is an alias.
 */
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

/**
 * __IfAliasIsEmpty - Handles case when alias table is empty.
 * @str: Input string containing new alias.
 * @src: Container holding alias data.
 */
void __IfAliasIsEmpty(char *str, t_container *src)
{
	src->alias.name = malloc(sizeof(char *) * 2);
	src->alias.value = malloc(sizeof(char *) * 2);
	src->alias.name[0] = get_name_or_value(str, NAME);
	src->alias.value[0] = get_name_or_value(str, VALUE);
	src->alias.name[1] = NULL;
	src->alias.value[1] = NULL;
}

/**
 * __new_alias_table - Updates the alias table with new values.
 * @src: Container holding alias data.
 * @name: Array containing new alias names.
 * @value: Array containing new alias values.
 */
void __new_alias_table(t_container *src, char **name, char **value)
{
	_free(src->alias.name, NULL, 1);
	_free(src->alias.value, NULL, 1);
	src->alias.name = name;
	src->alias.value = value;
}
