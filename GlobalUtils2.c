#include "simple_shell.h"

/**
 * get_HOME_dir - Retrieves the value of the HOME environment variable
 * @src: the src.
 * Return: A pointer to the value of the HOME environment variable,
 *         or NULL if it is not found.
 */
char *get_HOME_dir(t_container *src)
{
	char *path;
	int i = 0;

	path = NULL;
	for (; src->env[i]; i++)
	{
		if (!_strncmp("HOME", src->env[i], 4))
			path = _strdup(src->env[i]);
	}
	if (!path)
		return (NULL);
	return (_strcpy(path, path + 5));
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to be duplicated.
 *
 * Return: If successful, a pointer to the newly allocated duplicated string.
 *         If memory allocation fails or str is NULL, returns NULL.
 */
char *_strdup(char *str)
{
	int i;
	char *s_malloc;

	if (!str)
		return (NULL);
	i = (int)_strlen(str);
	s_malloc = (char *)malloc(sizeof(char) * i + 1);
	if (!s_malloc)
		return (NULL);
	s_malloc = _strcpy(s_malloc, str);
	s_malloc[i] = 0;
	return (s_malloc);
}

/**
 * __strjoin - Concatenates two strings with a space between
 * @s1: The first string
 * @s2: The second string
 *
 * Return: A new string containing the concatenated result
 */
char	*__strjoin(char *s1, char *s2)
{
	char	*arr;
	size_t	s1_len, s2_len, i, len;

	i = -1;
	len = 0;
	s1_len = _strlen(s1);
	s2_len = _strlen(s2);
	if (s1_len + s2_len == 0)
	{
		free(s1);
		return (NULL);
	}
	arr = malloc(s1_len + s2_len + 3);
	while (++i < s1_len)
		arr[i] = s1[i];
	arr[i++] = 32;
	while (i < (s1_len + s2_len) + 1)
		arr[i++] = s2[len++];
	arr[i] = 0;
	free(s1);
	return (arr);
}

/**
 * GetVarLent_str - Determines the length of a variable name in a string format
 * @str: The string containing the variable
 *
 * Return: The length of the variable name
 */
int GetVarLent_str(char *str)
{
	int i = 0;

	while (str && str[i] && str[i] != '$')
		i++;
	return (i);
}

/**
 * GetVarLent - Determines the length of a variable assignment in a string
 * @str: The string containing the variable assignment
 *
 * Return: The length of the variable assignment
 */
int GetVarLent(char *str)
{
	int i = 0;

	while (str && str[i] && str[i] != '$' && str[i] != '=')
		i++;
	return (i);
}
