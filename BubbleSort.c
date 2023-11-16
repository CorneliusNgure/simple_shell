#include "simple_shell.h"

/**

 * custom_tolower - custom implementation of character to lowercase conversion.
 * @c: the character to convert.
 *
 * Return: the lowercase equivalent of the input character.
 */

char _tolower(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c + ('a' - 'A'));
	}
	return (c);
}

/**
 * _strcasecmp - implementation of case-insensitive string comparison.
 * @s1: the first string.
 * @s2: the second string.
 *
 * Return:
 *   - 0 if the strings are equal,
 *   - a negative value if s1 is less than s2,
 *   - a positive value if s1 is greater than s2.
 */

int _strcasecmp(const char *s1, const char *s2)
{
	while (*s1 && _tolower(*s1) == _tolower(*s2))
	{
		s1++;
		s2++;
	}
	return (_tolower(*s1) - _tolower(*s2));
}

/**

 * _swap - swaps two string pointers.
 * @a: pointer to the first string.
 * @b: pointer to the second string.
 */

void _swap(char **a, char **b)
{
	char *temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * _bubbleSort - custom implementation of bubble sort for case-insensitive comparison.
 * @args: array of strings to be sorted.
 * @n: number of elements in the array.
 */

void _bubbleSort(char *args[], int n)
{
	int i, j;

	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (_strcasecmp(args[j], args[j + 1]) > 0)
			{
				_swap(&args[j], &args[j + 1]);
			}
		}
	}
}

