#include "simple_shell.h"

char *get_HOME_dir(void)
{
	char *path;
	int i = 0;

	for (; environ[i]; i++)
	{
		if (!_strncmp("HOME", environ[i], 4))
			path = environ[i];
	}
	if (!path)
		return NULL;
	return (fix_path(path));
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to be duplicated.
 *
 * Return: If successful, a pointer to the newly allocated duplicated string.
 *         If memory allocation fails or str is NULL, returns NULL.
 */
char	*_strdup(char *str)
{
	int		i;
	char	*s_malloc;

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