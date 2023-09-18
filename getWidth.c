#include "main.h"

/**
 * getWidth - function calculates the width printed
 * @format: pointer to string that prints arguments
 * @i: variable pointer to arguments printed
 * @list: list of arguments printed
 * Return: return width
 */

int getWidth(const char *format, int *i, va_list list)
{
	int curr_b;
	int width = 0;

	for (curr_b = *i + 1; format[curr_b] != '\0'; curr_b++)
	{
		if (isDigit(format[curr_b]))
		{
			width *= 10;
			width += format[curr_b] - '0';
		}

		else if (format[curr_b] == '*')
		{
			curr_b++;
			width = va_arg(list, int);
			break;
		}

		else
			break;
	}
	*i = curr_b - 1;

	return (width);
}
