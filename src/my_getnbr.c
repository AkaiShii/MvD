/*
** EPITECH PROJECT, 2017
** my_getnbr.c
** File description:
** returns number by a string
*/

int my_getnbr(char const *str)
{
	int i = 0;
	int neg = 0;
	int result = 0;
	int n = 0;

	if (str[0] == '0' && str[1] == '\0')
		return (0);
	while (str[i] != '\0' && n == 0) {
		if (str[i] == '-')
			neg = neg + 1;
		else if (str[i] <= '9' && str[i] >= '0')
			result = result * 10 + str[i] - 48;
		else if (str[i] == '+')
			n = 0;
		else
			n = 1;
		i = i + 1;
	}
	if (neg % 2 == 1)
		result = result * -1;
	return (result);
}
