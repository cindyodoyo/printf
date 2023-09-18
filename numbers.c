#include "main.h"

/**
 * printUnsigned - Prints an unsigned number
 * @args: List of arguments
 * @buffer: Buffer array to handle printing
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int printUnsigned(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	int m = BUFF_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);

	number = convertSizeUnsgnd(number, size);

	if (number == 0)
		buffer[m--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[m--] = (number % 10) + '0';
		number /= 10;
	}
	m++;

	return (writeUnsgnd(0, m, buffer, flags, width, precision, size));
}

/**
 * printOctal - Prints an unsigned number in octal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle printing
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printOctal(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	int m = BUFF_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int value = number;

	UNUSED(width);

	number = convertSizeUnsgnd(number, size);

	if (number == 0)
		buffer[m--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[m--] = (number % 8) + '0';
		number /= 8;
	}

	if (flags & F_HASH && value != 0)
		buffer[m--] = '0';
	m++;

	return (writeUnsgnd(0, m, buffer, flags, width, precision, size));
}

/**
 * printHexadecimal - Prints an unsigned number in hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle printing
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printHexadecimal(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	return (printHex(args, "0123456789abcdef", buffer, flags, 'x',
				width, precision, size));
}

/**
 * printHexadecimalUpper - Prints an unsigned number in
 * upper hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer array to handle printing
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printHexadecimalUpper(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	return (printHex(args, "0123456789ABCDEF", buffer, flags, 'X',
				width, precision, size));
}

/**
 * printHex - Prints a hexadecimal number in lower or upper case
 * @args: List of arguments
 * @mapToArray: Array of values to map the number to
 * @buffer: Buffer array to handle printing
 * @flags: Calculates active flags
 * @flagCh: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printHex(va_list args, char mapToArray[], char buffer[], int flags,
		char flagCh, int width, int precision, int size)
{
	int m = BUFF_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int value = number;

	UNUSED(width);

	number = convertSizeUnsgnd(number, size);

	if (number == 0)
		buffer[m--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[m--] = mapToArray[number % 16];
		number /= 16;
	}


	if (flags & F_HASH && value != 0)
	{
		buffer[m--] = flagCh;
		buffer[m--] = '0';
	}

	m++;


	return (writeUnsgnd(0, m, buffer, flags, width, precision, size));
}
