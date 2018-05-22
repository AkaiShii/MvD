/*
** EPITECH PROJECT, 2017
** my_strcat.c
** File description:
** Concatenates two strings
*/

#include "game.h"

char *my_strcat(char *dest, char const *src)
{
	int i = 0;
	int a = my_strlen(dest);
	int b = my_strlen(src);
	char *final = malloc(sizeof(char) * (a + b) + 1);

	for (; dest[i] != '\0'; i++)
		final[i] = dest[i];
	for (int c = 0; src[c] != '\0'; c++) {
		final[i] = src[c];
		i++;
	}
	final[i] = '\0';
	return (final);
}
