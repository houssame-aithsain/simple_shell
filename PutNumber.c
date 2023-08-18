#include "simple_shell.h"

void	_printnbr(char num)
{
	write (2, &num, 1);
}

void	_putnbr(int number)
{
	int	num;

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
