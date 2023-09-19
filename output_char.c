#include "main.h"

/************************* OUTPUT CHAR *************************/

/**
 * output_char - function that prints character
 * @types: argument list printed
 * @buffer: Buffer array to handle printing
 * @flags: Flags for formatting
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */

int output_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handleWriteChar(c, buffer, flags, width, precision, size));

}

/************************* OUTPUT A STRING *************************/

/**
 * output_string - function prints a string
 * @types: argument list printed
 * @buffer: Buffer array to handle printing
 * @flags: Flags for formatting
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */

int output_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = 0, b;

	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)

	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);

			for (b = width - length; b > 0; b--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (b = width - length; b > 0; b--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}

/************************* OUTPUT PERCENT SIGN *************************/

/**
 * output_percent - function prints a percent sign
 * @types: argument list printed
 * @buffer: buffer array to handle printing
 * @flags: Flags for formatting
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */

int outputt_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	return (write(1, "%%", 1));
}


/************************* OUTPUT INT *************************/

/**
 * output_int - function prints an integer
 * @types: argument list
 * @buffer: buffer array that handles printing
 * @flags: flags for formatting
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numberof characters printed
 */

int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int b = BUFF_SIZE - 2;

	int is_negative = 0;

	long int t = va_arg(types, long int);
	unsigned long int num;

	t = convertSizeNumber(t, size);

	if (t == 0)
		buffer[b--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)t;

	if (t < 0)
	{
		num = (unsigned long int)((-1) * t);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[b--] = (num % 10) + '0';
		num /= 10;
	}
	b++;

	return (writeNumber(is_negative, b, buffer, flags, width, precision, size));
}

/************************* OUTPUT BINARY *************************/

/**
 * output_binary - function prints binary number
 * @types: argument list printed
 * @buffer: buffer array to handle printing
 * @flags: Flags for formatting
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */

int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int t, r, b, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	t = va_arg(types, unsigned int);
	r = 2147483648; /* (2 ^ 31) */
	a[0] = t / r;

	for (b = 1; b < 32; b++)
	{
		r /= 2;
		a[b] = (t / r) % 2;
	}

	for (b = 0, sum = 0, count = 0; b < 32; b++)
	{
		sum += a[b];

		if (sum || b == 31)
		{
			char y = '0' + a[b];

			write(1, &y, 1);
			count++;
		}
	}

	return (count);
}
