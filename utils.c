#include "simple_shell.h"

/**
 * _atoi - Converts a string to an integer
 * @s: The string to convert
 *
 * Return: The converted integer
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int result = 0;
	int started = 0;

	while (*s)
	{
		if (*s == '-')
			sign *= -1;

		if (*s >= '0' && *s <= '9')
		{
			result = result * 10 + (*s - '0');
			started = 1;
		}
		else if (started)
		{
			break;
		}

		s++;
	}

	return (result * sign);
}

/**
 * _strcmp - Compares two strings
 * @s1: Pointer to the first string
 * @s2: Pointer to the second string
 *
 * Return: Integer value indicating the comparison result
 *   - Less than 0 if s1 is less than s2
 *   - 0 if s1 is equal to s2
 *   - Greater than 0 if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strcmp - Compares two strings
 * @s1: Pointer to the first string
 * @s2: Pointer to the second string
 *
 * Return: Integer value indicating the comparison result
 *   - Less than 0 if s1 is less than s2
 *   - 0 if s1 is equal to s2
 *   - Greater than 0 if s1 is greater than s2
 */
int	_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] == 0 && ((unsigned char *)s2)[i] != 0)
			return (-1);
		if (((unsigned char *)s1)[i] != 0 && ((unsigned char *)s2)[i] == 0)
			return (1);
		if (((unsigned char *)s1)[i] == 0 && ((unsigned char *)s2)[i] == 0)
			return (0);
		if (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i] != 0)
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/**
 * _strcpy - Copies the string pointed to by src to the buffer.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Return: The pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

void _free(char **d_pointer, char *pointer, int flag)
{
    int i = 0;

    if (flag == 1)
    {
        while (d_pointer[i])
            free(d_pointer[i++]);
        free(d_pointer);
    }
    else if (flag == -1)
    {
        free(pointer);
        while (d_pointer[i])
            free(d_pointer[i++]);
        free(d_pointer);
    }
    else
        free(pointer);
}

/**
 * _strlen - Calculates the length of a string.
 * @s: Pointer to the string.
 *
 * Description: This function calculates the length of a string by
 *              iterating through the characters until it reaches
 *              the null terminator ('\0').
 *
 * Return: The length of the string.
 */
size_t _strlen(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

/**
 * _countit - Counts the number of substrings in a string based
 * on a delimiter character.
 * @s: The input string.
 * @c: The delimiter character.
 * @flag: switch the function ps.
 * Return: The number of substrings in the string.
 */
int _countit(char *s, char c, int flag)
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
	int j = _countit(str, c, 0);
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
			len = _countit(str, c, 1);
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
