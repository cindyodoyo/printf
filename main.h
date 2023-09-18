#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct format - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
void putchar_buffer(char buffer[], int *current_buffer);

/*print char_string.c prototypes*/
int output_char(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int output_string(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int outputt_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* numbers.c prototypes*/
int printUnsigned(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int printOctal(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int printHexadecimal(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int printHexadecimalUpper(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int printHex(va_list args, char mapToArray[], char buffer[], int flags,
		char flagCh, int width, int precision, int size);

/* pointer_string.c prototypes */
int printPointer(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int printNonPrintable(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int printReversed(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int printRot13String(va_list args, char buffer[],
		int flags, int width, int precision, int size);
/* Funciotns to handle width, size, precision and flags specifications */
int getWidth(const char *format, int *i, va_list list);
int getSize(const char *format, int *i);
int getPrecision(const char *format, int *i, va_list list);
int getFlags(const char *format, int *i);

/* handle_write_fnc.c prototypes */
int handleWriteChar(char character, char buffer[],
		int flags, int width, int precision, int size);
int writeNumber(int isNegative, int index_m, char buffer[],
		int flags, int width, int precision, int size);
int writePointer(char buffer[], int index, int length,
		int width, int flags, char paddingChar, char extraChar, int paddingStart);
int writeUnsgnd(int isNegative, int index,
		char buffer[], int flags, int width, int precision, int size);
int writeNum(int index, char buffer[], int flags, int width, int precision,
		int length, char paddingChar, char extraChar);
/* function to handle print */
int handlePrint(const char *fmt, int *ind, va_list list, char buffer[],
		int flags, int width, int precision, int size);

/*helper_fncs.c prototypes*/
int appendHexaCode(char asciiCode, char buffer[], int startIndex);
int isDigit(char character);
int isPrintable(char character);
long int convertSizeNumber(long int number, int size);
unsigned long int convertSizeUnsgnd(unsigned long int number, int size);

#endif /* MAIN_H */

