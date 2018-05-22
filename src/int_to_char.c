/*
** EPITECH PROJECT, 2018
** CHAOSDUEL
** File description:
** youpie
*/

#include <stdlib.h>

char *my_revstr(char *str)
{
	char buffer;
	int comp = 0;
	int comp_inv = 0;

	while (str[comp_inv] != '\0')
		comp_inv = comp_inv + 1;
	comp_inv = comp_inv - 1;
	while (comp_inv > comp) {
		buffer = str[comp_inv];
		str[comp_inv] = str[comp];
		str[comp] = buffer;
		comp_inv = comp_inv - 1;
		comp = comp + 1;
	}
	return (str);
}

char *int_to_char(int a)
{
	char *str;
	int count = 0;
	int b = a;

	if (a == 0)
		return ("0");
	while (b != 0) {
		b = b / 10;
		count += 1;
	}
	str = malloc(sizeof(char) * count + 1);
	str[count] = '\0';
	count = 0;
	while (a != 0) {
		str[count] = a % 10 + 48;
		a = a / 10;
		count += 1;
	}
	return (my_revstr(str));
}
