#include "simple_shell.h"

/**
 * _strjoin - Concatenates two strings.
 * @s1: First string.
 * @s2: Second string.
 * Return: New string containing concatenated s1 and s2.
 */
char	*_strjoin(char *s1, char *s2)
{
	char	*arr;
	size_t	s1_len, s2_len, i, cp;

	i = -1;
	cp = 0;
	s1_len = _strlen(s1);
	s2_len = _strlen(s2);
	if (s1_len + s2_len == 0)
	{
		free(s1);
		return (0);
	}
	arr = malloc(s1_len + s2_len + 1);
	while (++i < s1_len)
		arr[i] = s1[i];
	while (i < (s1_len + s2_len))
		arr[i++] = s2[cp++];
	arr[i] = 0;
	free(s1);
	return (arr);
}

/**
 * _if_new_line - Checks if a string contains a new line character.
 * @buffer: Input string.
 * Return: 0 if new line character found, 1 otherwise.
 */
int	_if_new_line(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}
