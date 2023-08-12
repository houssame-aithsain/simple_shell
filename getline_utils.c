#include "simple_shell.h"

char	*_strjoin(char *s1, char *s2)
{
	char	*arr;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	m;

	k = -1;
	m = 0;
	i = _strlen(s1);
	j = _strlen(s2);
	if (i + j == 0)
	{
		free(s1);
		return (0);
	}
	arr = malloc(i + j + 1);
	while (++k < i)
		arr[k] = s1[k];
	while (k < (i + j))
		arr[k++] = s2[m++];
	arr[k] = 0;
	free(s1);
	return (arr);
}

int	_check_new_line(char *buffer)
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
