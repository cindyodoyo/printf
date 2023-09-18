#include "main.h"

/**
 * getFlags - a function that retrieves active flags
 * @format: pointer to a string that shows formatted arguments
 * @i: variable that retries flags
 * Return: returns flags
 */

int getFlags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */

	int a, curr_b;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_b = *i + 1; format[curr_b] != '\0'; curr_b++)
	{
		for (a = 0; FLAGS_CH[a] != '\0'; a++)

			if (format[curr_b] == FLAGS_CH[a])
			{
				flags |= FLAGS_ARR[a];
				break;
			}

		if (FLAGS_CH[a] == 0)
			break;
	}
	*i = curr_b - 1;

	return (flags);
}
