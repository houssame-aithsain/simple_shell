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
	int started = 0;
	unsigned int result = 0;

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
 * _strncmp - Compares two strings lexicographically up to n characters
 * @s1: Pointer to the first string
 * @s2: Pointer to the second string
 * @n: Number of characters to compare
 *
 * Return: Integer value indicating the comparison result
 *   - Less than 0 if s1 is lexicographically less than s2
 *   - 0 if s1 is lexicographically equal to s2
 *   - Greater than 0 if s1 is lexicographically greater than s2
 */
int	_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i = 0;

	while (i < n)
	{
		if (!s1[i] && s2[i])
			return (-1);
		if (s1[i] && !s2[i])
			return (1);
		if (!s1[i] && !s2[i])
			return (0);
		if (s1[i] - s2[i])
			return (s1[i] - s2[i]);
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

/**
 * _free - Frees allocated memory for an array of strings
 * and/or a single string.
 * @d_pointer: Double pointer to an array of strings.
 * @pointer: Pointer to a single string.
 * @flag: Indicator for the memory freeing scenario:
 *        1: Free array of strings.
 *       -1: Free single string and array of strings.
 *        0: Free only a single string.
 */
void _free(char **d_pointer, char *pointer, int flag)
{
	int i = 0;

	if (flag == 1)
	{
		while (d_pointer && d_pointer[i])
			free(d_pointer[i++]);
		if (d_pointer)
			free(d_pointer);
	}
	else if (flag == -1)
	{
		if (pointer)
			free(pointer);
		while (d_pointer && d_pointer[i])
			free(d_pointer[i++]);
		if (d_pointer)
			free(d_pointer);
	}
	else
	{
		if (pointer)
			free(pointer);
	}
}
