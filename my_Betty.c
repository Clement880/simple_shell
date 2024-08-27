#include <stdio.h>

/**
 * fact - calculates the factorial of a non-negative integer.
 * @n: the integer for which to calculate the factorial.
 *
 * Return: fact of the integer, or (-1) if the integer is negative.
 */
int fact(int n)
{
	if (n < 0)
	{
		return (-1);
	}
	if (n == 0 || n == 1)
	{
		return (1);
	}
	return (n * fact(n - 1));
}

/**
 * main - main entry point of the program.
 *
 * Return: (0) on Success Always
 */
int main(void)
{
	int num = 5;
	int res;

	res = fact(num);

	if (res != -1)
	{
		printf("%d\n", res);
	}
	else
	{
		printf("fact\n");
	}

	return (0);
}
