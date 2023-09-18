#include "main.h"

/**
 * getPrecision -function  retrieves the precision for printing
 * @format: pointer string showing printed arguments
 * @i: variable pointer to printed arguments
 * @list: list of printed arguments
 * Return: return precision
 */

int getPrecision(const char *format, int *i, va_list list)
{
	int curr_b = *i + 1;
	int precision = -1;

	if (format[curr_b] != '.')
		return (precision);

	precision = 0;

	for (curr_b += 1; format[curr_b] != '\0'; curr_b++)
	{
		if (is_digit(format[curr_i]))
		{
			precision *= 10;
			precision += format[curr_b] - '0';
		}

		else if (format[curr_b] == '*')
		{
			curr_b++;
			precision = va_arg(list, int);
			break;
		}

		else
			break;
	}
	*i = curr_b - 1;

	return (precision);
}
