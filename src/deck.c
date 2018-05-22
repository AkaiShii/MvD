
#include "game.h"

card *load_deck(char *path)
{
	FILE *fd = fopen(path, "r");
	char *line = NULL;
	size_t len = 0;
	card *new = malloc(sizeof(card) * 30);

	if (fd == NULL)
		return (new);
	for (int i = 0; i < 30; i++) {
		if (getline(&line, &len, fd) == -1)
			break;
		printf("%s\n", line);
		new[i] = create_card(my_strcpy_n(line));
	}
	fclose(fd);
	return (new);
}	

void melanger(game *s)
{
	int nbr = 0;
	card swap;

	for (int i = 0; i < 30; i++) {
		nbr = rand() % 30;
		swap = copy_card(s->p.j1.deck[i]);
		s->p.j1.deck[i] = copy_card(s->p.j1.deck[nbr]);
		s->p.j1.deck[nbr] = copy_card(swap);
	}
}
