#include "simple_shell.h"

char	*get_after_new_line(char *container)
{
	char	*arr;
	size_t	i, c_len, buf_len, cp;

	buf_len = 0;
	i = 0;
	c_len = _strlen(container);
	while (container && container[i] && container[i] != '\n')
		i++;
	if (!container || !container[i] || (container[i] == '\n'
			&& container[i + 1] == '\0'))
	{
		free(container);
		return (NULL);
	}
	i++;
	cp = i;
	arr = malloc((c_len - i) + 1);
	while (buf_len < c_len - i)
		arr[buf_len++] = container[cp++];
	arr[buf_len] = 0;
	free(container);
	return (arr);
}

char	*get_befor_new_line(char *container)
{
	char	*arr;
	size_t	len;
	size_t	i;

	if (!container)
		return (NULL);
	i = 0;
	len = 0;
	while (container[i] && container[i] != '\n')
		i++;
	if (container[i] == '\n')
		i++;
	arr = malloc(i + 1);
	if (!arr)
		return (NULL);
	while (len < i)
	{
		arr[len] = container[len];
		len++;
	}
	arr[len] = 0;
	return (arr);
}

char	*get_line_copy(int fd, char *container)
{
	char	*buffer;
	int		size;

	size = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (size > 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1)
		{
			free(container);
			free(buffer);
			return (0);
		}
		buffer[size] = 0;
		container = _strjoin(container, buffer);
		if (!_if_new_line(buffer))
			break ;
	}
	free(buffer);
	return (container);
}

char	*_getline(int fd)
{
	static char	*container;
	char		*holder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!container)
	{
		container = malloc(1);
		if (!container)
			return (NULL);
		container[0] = '\0';
	}
	container = get_line_copy(fd, container);
	holder = get_befor_new_line(container);
	container = get_after_new_line(container);
	if (!holder)
	{
		free(container);
		return (NULL);
	}
	return (holder);
}
