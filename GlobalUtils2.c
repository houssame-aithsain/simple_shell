#include "simple_shell.h"

char *get_HOME_dir(void)
{
	char *path;
	int i = 0;

	for (; environ[i]; i++)
	{
		if (!_strncmp("HOME", environ[i], 4))
			path = _strdup(environ[i]);
	}
	if (!path)
		return NULL;
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