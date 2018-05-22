
#include "game.h"

void save_account(game *s)
{
	int fd;

	remove("acc/my");
	fd = open("acc/my", O_WRONLY | O_CREAT, S_IRUSR);
	if (fd == -1)
		return;
	write(fd, s->c.name, strlen(s->c.name));
	write(fd, "\n", 1);
	if (s->c.titre == NULL)
		write(fd, "\n", 1);
	else
		write(fd, s->c.titre, strlen(s->c.titre));
	write(fd, int_to_char(s->c.gold), strlen(int_to_char(s->c.gold)));
	write(fd, "\n", 1);
	write(fd, int_to_char(s->c.deck), strlen(int_to_char(s->c.deck)));
	write(fd, "\n", 1);
	write(fd, int_to_char(s->c.cards), strlen(int_to_char(s->c.cards)));
	write(fd, "\n", 1);
	close(fd);
}

void create_account(game *s)
{
	creat("acc/my", S_IRUSR);
	creat("acc/deck", S_IRUSR);
	creat("acc/card", S_IRUSR);
	s->c.name = text_entered(s);
	s->c.titre = NULL;
	s->c.gold = 0;
	s->c.deck = 0;
	s->c.cards = 0;
	s->c.collection = calloc(1, 1);
	save_account(s);
}

void load_account(game *s)
{
	FILE *fd = fopen("acc/my", "r");
	char *line = NULL;
	size_t len = 0;

	if (fd == NULL)
		return;
	getline(&line, &len, fd);
	s->c.name = my_strcpy_n(line);
	getline(&line, &len, fd);
	s->c.titre = my_strcpy_n(line);
	getline(&line, &len, fd);
	s->c.gold = my_getnbr(line);
	getline(&line, &len, fd);
	s->c.deck = my_getnbr(line);
	getline(&line, &len, fd);
	s->c.cards = my_getnbr(line);
	fclose(fd);
	s->c.collection = malloc(sizeof(card) * s->c.cards);
	fd = fopen("acc/card", "r");
	for (int i = 0; i < s->c.cards; i++) {
		getline(&line, &len, fd);
		s->c.collection[i] = create_card(my_strcpy_n(line));
	}
	free(line);
	fclose(fd);
}

int check_account(void)
{
	int fd = open("acc/my", O_RDONLY);

	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}
