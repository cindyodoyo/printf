#include "main.h"

/**
 * printPointer - Prints the value of a pointer variable
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int printPointer(va_list args, char buffer[],
		int flags, int width, int precision, int size)
{
	char extraChar = 0, paddingChar = ' ';
	int position = BUFF_SIZE - 2, length = 2, paddingStart = 1;
	unsigned long address;
	char mapToArray[] = "0123456789abcdef";

	void *ptr = va_arg(args, void *);

	UNUSED(width);
	UNUSED(size);

	if (ptr == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	address = (unsigned long)ptr;

	while (address > 0)
	{
		buffer[position--] = mapToArray[address % 16];
		address /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';


	if (flags & F_PLUS)
		extraChar = '+', length++;
	else if (flags & F_SPACE)
		extraChar = ' ', length++;

	position++;


	return (writePointer(buffer, position, length,
				width, flags, paddingChar, extraChar, paddingStart));
}

/**
 * printNonPrintable - Prints ASCII codes in hexadecimal of
 * non-printable characters
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printNonPrintable(va_list args, char buffer[],
		int flags, int width, int precision, int size)
{
	int m = 0, start = 0;
	char *string = va_arg(args, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);


	if (string == NULL)
		return (write(1, "(null)", 6));


	while (string[m] != '\0')
	{
		if (isPrintable(string[m]))
			buffer[m + start] = string[m];
		else
			start += appendHexaCode(string[m], buffer, m + start);

		m++;
	}

	buffer[m + start] = '\0';

	return (write(1, buffer, m + start));
}

/**
 * printReversed - Prints a reversed string.
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printReversed(va_list args, char buffer[],
		int flags, int width, int precision, int size)
{
	char *string;
	int m, counter = 0;


	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	string = va_arg(args, char *);


	if (string == NULL)
	{
		UNUSED(precision);

		string = ")Null(";
	}

	for (m = 0; string[m]; m++)
		;
	for (m = m - 1; m >= 0; m--)
	{
		char ch = string[m];

		write(1, &ch, 1);
		counter++;
	}


	return (counter);
}

/**
 * printRot13String - Print a string in ROT13.
 * @args: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int printRot13String(va_list args, char buffer[],
		int flags, int width, int precision, int size)
{
	char character;
	char *string;
	unsigned int m, n;
	int counter = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	string = va_arg(args, char *);

	if (string == NULL)
		string = "(AHYY)";
	if (string != NULL)
	{
		for (m = 0; string[m]; m++)
		{
			for (n = 0; input[n]; n++)
			{
				if (input[n] == string[m])
				{
					character = output[n];
					write(1, &character, 1);
					counter++;
					break;
				}
			}
			if (!input[n])
			{
				character = string[m];
				write(1, &character, 1);
				counter++;
			}
		}
	}
	return (counter);
}

