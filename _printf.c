#include "main.h"

void putchar_buffer(char buffer[], int *current_buffer);

/**
 * _printf - Custom printf function
 * @format: The format string
 * @...: Variable number of arguments
 *
 * Return: The number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int m, output = 0, printed_chars = 0;
	int width, precision, flags, size, current_buffer = 0;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (m = 0; format && format[m] != '\0'; m++)
	{
		if (format[m] != '%')
		{
			buffer[current_buffer++] = format[m];
			if (current_buffer == BUFF_SIZE)
				putchar_buffer(buffer, &current_buffer);
			printed_chars++;
		}
		else
		{
			putchar_buffer(buffer, &current_buffer);
			flags = getFlags(format, &m);
			width = getWidth(format, &m, args);
			precision = getPrecision(format, &m, args);
			size = getSize(format, &m);
			m++;
			output = handlePrint(format, &m, args,
					buffer, flags, width, precision, size);
			if (output == -1)
				return (-1);
			printed_chars += output;
		}
	}
	putchar_buffer(buffer, &current_buffer);

	va_end(args);
	return (printed_chars);
}

/**
 * putchar_buffer - a function that prints the buffer
 *
 * @buffer: arays of characters
 * @current_buffer: index to which the next character is added as per buffer
 * length
 */
void putchar_buffer(char buffer[], int *current_buffer)
{
	if (*current_buffer > 0)
		write(1, &buffer[0], *current_buffer);
	*current_buffer = 0;
}

