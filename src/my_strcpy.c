/*
** EPITECH PROJECT, 2017
** my_strcpy.c
** File description:
** return dest
*/

#include "game.h"

int my_strlen(char const *str)
{
	int c = 0;

	while (str[c])
		c++;
	return (c);
}

char *my_strcpy(const char *src)
{
	int x = 0;
	char *dest = malloc(sizeof(char) * my_strlen(src) + 1);

	while (src[x] != '\0') {
		dest[x] = src[x];
		x = x + 1;
	}
	dest[x] = '\0';
	return (dest);
}

char *my_strcpy_n(char const *src)
{
	int x = 0;
	char *dest = calloc(1, my_strlen(src) + 1);
	//char *dest = malloc(sizeof(char) * my_strlen(src));

	while (src[x] != '\n') {
		if (src[x] == '\0')
			break;
		dest[x] = src[x];
		x = x + 1;
	}
	dest[x] = '\0';
	return (dest);
}
