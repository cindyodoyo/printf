#include "main.h"

/**
 * handlePrint - function that Prints  arguments
 * @fmt: pointer to a string that prints arguments
 * @list: argument list with values to be printed
 * @ind: pointer to an integer that updates indexing
 * @buffer: an array of charactersthat stores formatted output
 * @flags: integer paremeter containing flags
 * @width: integer specifying width output
 * @precision: specifies characters to be printed for strings
 * @size: indicates the size of data type formatted
 * Return: returns number
 */

int handlePrint(const char *fmt, int *ind, va_list list, char buffer[],
		int flags, int width, int precision, int size)
{
	int b, unknow_len = 0, printed_chars = -1;

	fmt_t fmt_types[] = {

		{'c', print_char}, {'s', print_string}, {'%', print_percent},

		{'i', print_int}, {'d', print_int}, {'b', print_binary},

		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},

		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},

		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	for (b = 0; fmt_types[b].fmt != '\0'; b++)

		if (fmt[*ind] == fmt_types[b].fmt)
			return (fmt_types[b].fn(list, buffer, flags, width, precision, size));
	if (fmt_types[b]fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);

			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
