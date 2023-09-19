#include "main.h"

/**
 * isPrintable - Checks if a character is printable
 * @character: Character to be checked.
 *
 * Return: 1 if the character is printable, 0 otherwise
 */
int isPrintable(char character)
{
	if (character >= 32 && character < 127)
		return (1);

	return (0);
}

/**
 * appendHexaCode - Appends ASCII in hexadecimal code to the buffer
 * @buffer: Character buffer.
 * @startIndex: Index at which to start appending.
 * @asciiCode: ASCII CODE.
 *
 * Return: Always 3.
 */
int appendHexaCode(char asciiCode, char buffer[], int startIndex)
{
	char hexMapArray[] = "0123456789ABCDEF";


	if (asciiCode < 0)
		asciiCode *= -1;

	buffer[startIndex++] = '\\';
	buffer[startIndex++] = 'x';

	buffer[startIndex++] = hexMapArray[asciiCode / 16];
	buffer[startIndex] = hexMapArray[asciiCode % 16];

	return (3);
}

/**
 * isDigit - Checks if a character is a digit
 * @character: Character to be checked.
 *
 * Return: 1 if the character is a digit, 0 otherwise
 */
int isDigit(char character)
{
	if (character >= '0' && character <= '9')
		return (1);

	return (0);
}

/**
 * convertSizeNumber - Casts a number to the specified size
 * @number: Number to be casted.
 * @size: Size specifier indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convertSizeNumber(long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * convertSizeUnsgnd - Casts an unsigned number to the specified size
 * @number: Unsigned number to be casted.
 * @size: Size specifier indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convertSizeUnsgnd(unsigned long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}

