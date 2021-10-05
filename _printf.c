#include "main.h"
#include <stdlib.h>

/**
 * check_for_specifiers - checks if there is a valid format specifier
 * @format: possible format specifier
 *
 * Return: pointer to valid function or NULL
 */
static int (*check_for_specifiers(const char *format))(va_list)
{
	unsigned int i;
	print_t p[] = {
		{"c", print_c},
		{"s", print_s},
		{"i", print_i},
		{"d", print_d},
		{"u", print_u},
		{"b", print_b},
		{"o", print_o},
		{"x", print_x},
		{"X", print_X},
		{"p", print_p},
		{"S", print_S},
		{"r", print_r},
		{"R", print_R},
		{NULL, NULL}
	};

	for (i = 0; p[i].t != NULL; i++)
	{
		if (*(p[i].t) == *format)
		{
			break;
		}
	}
	return (p[i].f);
}

/**
 * _printf - prints anything
 * @format: list of argument types passed to the function
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	unsigned int i = 0, count = 0;
	va_list valist;
	int (*f)(va_list);

	if (format == NULL)
		return (-1);
	va_start(valist, format);
	while (format[i])
	{
		for (; format[i] != '%' && format[i]; i++)
		{
			_putchar(format[i]);
			count++;
		}
		if (!format[i])
			return (count);
		f = check_for_specifiers(&format[i + 1]);
		if (f != NULL)
		{
			count += f(valist);
			i += 2;
			continue;
		}
		if (!format[i + 1])
			return (-1);
		_putchar(format[i]);
		count++;
		if (format[i + 1] == '%')
			i += 2;
		else
			i++;
	}
	va_end(valist);
	return (count);
=======
#include <unistd.h>
#include <stdio.h>
/**
* buffer_print - print given buffer to stdout
* @buffer: buffer to print
* @nbytes: number of bytes to print
* Return: nbytes
*/
int buffer_print(char buffer[], unsigned int nbytes)
{
write(1, buffer, nbytes);
return (nbytes);
}
/**
 * buffer_add - adds a string to buffer
 * @buffer: buffer to fill
 * @str: str to add
 * @buffer_pos: pointer to buffer first empty position
 *
 * Return: if buffer filled and emptyed return number of printed char
 * else 0
 */
int buffer_add(char buffer[], char *str, unsigned int *buffer_pos)
{
int i = 0;
unsigned int count = 0, pos = *buffer_pos, size = BUFFER_SIZE;
while (str && str[i])
{
if (pos == size)
{
count += buffer_print(buffer, pos);
pos = 0;
}
buffer[pos++] = str[i++];
}
*buffer_pos = pos;
return (count);
}
/**
 * _printf - produces output according to a format
 * @format: character string
 *
 * Return: the number of characters printed excluding the null byte
 * used to end output to strings
 */
int _printf(const char *format, ...)
{
va_list ap;
unsigned int i = 0, buffer_pos = 0, count = 0;
char *res_str, *aux, buffer[BUFFER_SIZE];
if (!format || !format[0])
return (-1);
va_start(ap, format);
aux = malloc(sizeof(char) * 2);
while (format && format[i])
{
if (format[i] == '%')
{
res_str = treat_format(format, &i, ap);
count += buffer_add(buffer, res_str, &buffer_pos);
free(res_str);
}
else
{
aux[0] = format[i++];
aux[1] = '\0';
count += buffer_add(buffer, aux, &buffer_pos);
}
}
count += buffer_print(buffer, buffer_pos);
free(aux);
va_end(ap);
if (!count)
count = -1;
return (count);
}
