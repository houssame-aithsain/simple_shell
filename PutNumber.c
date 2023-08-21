#include "simple_shell.h"

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
 * _printnbr - Prints a single digit number to the standard error stream
 * @num: Number to print
 *
 * Prints a single digit @num to the standard error stream using write().
 */
void _printnbr(char num)
{
	write(2, &num, 1);
}

/**
 * _putnbr - Prints an integer to the standard error stream
 * @number: Integer to print
 *
 * Prints the integer @number to the standard error stream using _printnbr().
 */
void _putnbr(int number)
{
	int num;

	num = number;
	if (num >= 0 && num <= 9)
		_printnbr((num) + '0');
	if (num == -2147483648)
	{
		_printnbr('-');
		_printnbr((2) + '0');
		num = 147483648;
	}
	if (num < 0)
	{
		_printnbr('-');
		_putnbr(num * -1);
	}
	else if (num > 9)
	{
		_putnbr(num / 10);
		_putnbr(num % 10);
	}
}

/**
 * __free_all - Frees memory and resources in the shell container
 * @src: Shell container to free
 *
 * Frees memory and resources allocated within the shell container @src.
 */
void __free_all(t_container *src)
{
	free(src->line);
	free(src->path);
	if (src->is_fd)
		free(src->fdLine);
	if (!src->is_fd)
		free(src->mainLine);
	free(src->cmd_path);
	_free(src->splitedLines, NULL, 1);
	_free(src->mc_arg, NULL, 1);
	_free(src->alias.name, NULL, 1);
	_free(src->alias.value, NULL, 1);
	_free(src->arg, NULL, 1);
	_free(src->env, NULL, 1);
}
