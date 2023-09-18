#include "main.h"

/**
 * getSize -function cCalculates the size the argument printed
 * @format: pointer to a string that prints arguments
 * i: variable pointer to the formatted arguments 
 * Return: return precision
 */

int getSize(const char *format, int *i)
{
	int curr_b = *i + 1;
	int size = 0;

	if (format[curr_b] == 'l')
		size = S_LONG;

	else if (format[curr_b] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_b - 1;

	else
		*i = curr_b;

	return (size);
}
