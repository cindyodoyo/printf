#include "main.h"

/**
 * handleWriteChar - Prints a character
 * @character: Character to be printed.
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int handleWriteChar(char character, char buffer[],
		int flags, int width, int precision, int size)
{
	int index = 0;
	char paddingChar = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		paddingChar = '0';

	buffer[index++] = character;
	buffer[index] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';

		for (index = 0; index < width - 1; index++)
			buffer[BUFF_SIZE - index - 2] = paddingChar;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - index - 1],
						width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - index - 1], width - 1)
					+ write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * writeNumber - Prints a number
 * @isNegative: Indicates if the number is negative.
 * @index_m: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int writeNumber(int isNegative, int index_m, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index_m - 1;
	char paddingChar = ' ', CharS = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';

	if (isNegative)
		CharS = '-';
	else if (flags & F_PLUS)
		CharS = '+';
	else if (flags & F_SPACE)
		CharS = ' ';

	return (writeNum(index_m, buffer, flags, width, precision,
				length, paddingChar, CharS));
}

/**
 * writeNum - Write a number using a buffer
 * @index: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width specifier.
 * @prec: Precision specifier.
 * @length: Number length.
 * @paddingChar: Padding character.
 * @extraChar: Extra character.
 *
 * Return: Number of characters printed.
 */
int writeNum(int index, char buffer[], int flags, int width, int prec,
		int length, char paddingChar, char extraChar)
{
	int m, paddingStart = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0);
	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = paddingChar = ' ';
	if (prec > 0 && prec < length)
		paddingChar = ' ';
	while (prec > length)
		buffer[--index] = '0', length++;
	if (extraChar != 0)
		length++;
	if (width > length)
	{
		for (m = 1; m < width - length + 1; m++)
			buffer[m] = paddingChar;
		buffer[m] = '\0';
		if (flags & F_MINUS && paddingChar == ' ')
		{
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], m - 1));
		}
		else if (!(flags & F_MINUS) && paddingChar == ' ')
		{
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[1], m - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && paddingChar == '0')
		{
			if (extraChar)
				buffer[--paddingStart] = extraChar;
			return (write(1, &buffer[paddingStart], m - paddingStart) + write(1,
						&buffer[index], length - (1 - paddingStart)));
		}
	}
	if (extraChar)
		buffer[--index] = extraChar;
	return (write(1, &buffer[index], length));
}

/**
 * writeUnsigned - Writes an unsigned number
 * @isNegative: Number indicating if the number is negative.
 * @index: Index at which the number starts in the buffer.
 * @buffer: Buffer array to handle print.
 * @flags: Flags specifier.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int writeUnsgnd(int isNegative, int index,
		char buffer[], int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, m = 0;
	char paddingChar = ' ';

	UNUSED(isNegative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0);

	if (precision > 0 && precision < length)
		paddingChar = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';

	if (width > length)
	{
		for (m = 0; m < width - length; m++)
			buffer[m] = paddingChar;

		buffer[m] = '\0';

		if (flags & F_MINUS)
			return (write(1, &buffer[index], length) + write(1, &buffer[0], m));
		else
			return (write(1, &buffer[0], m) + write(1, &buffer[index], length));
	}

	return (write(1, &buffer[index], length));
}

/**
 * writePointer - Write a memory address
 * @buffer: Buffer array to handle print.
 * @index: Index at which the number starts in the buffer.
 * @length: Length of the number.
 * @width: Width specifier.
 * @flags: Flags specifier.
 * @paddingChar: Padding character.
 * @extraChar: Extra character.
 * @paddingStart: Index at which padding should start.
 *
 * Return: Number of characters printed.
 */
int writePointer(char buffer[], int index, int length,
		int width, int flags, char paddingChar, char extraChar, int paddingStart)
{
	int m;

	if (width > length)
	{
		for (m = 3; m < width - length + 3; m++)
			buffer[m] = paddingChar;
		buffer[m] = '\0';
		if (flags & F_MINUS && paddingChar == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], m - 3));
		}
		else if (!(flags & F_MINUS) && paddingChar == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[3], m - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && paddingChar == '0')
		{
			if (extraChar)
				buffer[-- paddingStart] = extraChar;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[paddingStart], m - paddingStart) + write(1,
						&buffer[index], length - (1 - paddingStart) - 2));
		}
	}

	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extraChar)
		buffer[--index] = extraChar;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}

