#include "simple_shell.h"

int	ft_check_numb(long int n)
{
	int	i;

	i = 1;
	while (1)
	{
		if (n < 0)
		{
			i++;
			n *= -1;
		}
		n = n / 10;
		if (n)
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	int			x;
	long int	cast;
	char		*arr;

	cast = (long int)n;
	x = 0;
	i = ft_check_numb(cast);
	arr = malloc(((sizeof(char) * i) + 1));
	if (!arr)
		return (NULL);
	if (cast < 0)
	{
		arr[0] = '-';
		cast *= -1;
		x = 1;
	}
	arr[i] = 0;
	i--;
	while (i >= x)
	{
		arr[i--] = (cast % 10) + 48;
		cast = cast / 10;
	}
	return (arr);
}

/**
 * _substr - Extracts a substring from a given string.
 * @s: The input string.
 * @start: The starting index of the substring.
 * @len: The length of the substring.
 *
 * Return: The extracted substring.
 */
char *_substr(char *s, int start, size_t len)
{
	char *arr;
	int i;
	int j;

	i = 0;
	j = start;
	if (len > _strlen(s) - start)
		len = _strlen(s) - start;
	if (s[start] != '\0')
	{
		arr = malloc(len + 1);
		if (!arr)
			return (NULL);
		i = 0;
		while (len)
		{
			arr[i++] = s[j++];
			len--;
		}
		arr[i] = '\0';
		return (arr);
	}
	return (NULL);
}

/**
 * _str_len - Counts the number of substrings in a string based
 * on a delimiter character.
 * @s: The input string.
 * @c: The delimiter character.
 * @flag: switch the function ps.
 * Return: The number of substrings in the string.
 */
int _str_len(char *s, char c, int flag)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (flag)
	{
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		return (i);
	}
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

/**
 * strtow - Splits a string into an array of substrings based
 * on a delimiter character.
 * @str: The input string.
 *
 * Return: The array of substrings.
 */
char **strtow(char *str, char c)
{
	char **arr;
	int i = 0;
	int j = _str_len(str, c, 0);
	int len;

	if (!_strlen(str) || !j)
		return (NULL);
	arr = malloc(sizeof(char *) * (j + 1));
	if (!arr)
		return (NULL);
	while (*str)
	{
		if (*str != c)
		{
			len = _str_len(str, c, 1);
			arr[i] = _substr(str, 0, len);
			str += len;
			i++;
		}
		else
			str++;
	}
	arr[i] = NULL;
	return (arr);
}
