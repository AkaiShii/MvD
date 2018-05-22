
#include "game.h"

void destroy_cards(game *s)
{
	for (int i = 0; i < 5; i++)
		destroy(&s->cards[i].hand);
	free(s->cards);
}

card copy_card(card src)
{
	card new;

	new.name = my_strcpy(src.name);
	new.hand = create_sprite(my_strcat(src.name, ".png"), 0, 0);
	new.board = create_sprite(my_strcat(src.name, ".png"), 0, 0);
	new.id = src.id;
	new.atk = src.atk;
	new.hp = src.hp;
	new.unit = src.unit;
	new.mana = src.mana;
	new.rare = src.rare;
	new.spell = src.spell;
	new.play = 1;
	new.effet = malloc(sizeof(int) * new.spell);
	for (int i = 0; i < new.spell; i++)
		new.effet[i] = src.effet[i];
	return (new);
}

card verso(int x, int y)
{
	card new;

	new.name = "dos";
	new.id = 1;
	new.hand = create_sprite("dos.png", x, y);
	new.atk = 0;
	new.hp = 0;
	new.unit = 0;
	new.mana = 0;
	new.rare = 0;
	new.spell = 0;
	return (new);
}

card create_card(char *name)
{
	FILE *fd = fopen(my_strcat("card/", name), "r");
	size_t len = 0;
	char *line = NULL;
	card new;

	new.name = my_strcpy(name);
	new.hand = create_sprite(my_strcat(name, ".png"), 0, 0);
	new.board = create_sprite(my_strcat(name, ".png"), 0, 0);
	getline(&line, &len, fd);
	new.id = my_getnbr(line);
	getline(&line, &len, fd);
	new.atk = my_getnbr(line);
	getline(&line, &len, fd);
	new.hp = my_getnbr(line);
	getline(&line, &len, fd);
	new.unit = my_getnbr(line);
	getline(&line, &len, fd);
	new.mana = my_getnbr(line);
	getline(&line, &len, fd);
	new.rare = my_getnbr(line);
	getline(&line, &len, fd);
	new.spell = my_getnbr(line);
	new.effet = malloc(sizeof(int) * new.spell);
	for (int i = 0; i < new.spell; i++) {
		getline(&line, &len, fd);
		new.effet[i] = my_getnbr(line);
	}
	new.play = 1;
	return (new);
}

void init_cards(game *s)
{
	s->cards = malloc(sizeof(card) * 12);
	s->cards[0] = create_card("Ant-man");
	s->cards[1] = create_card("Captain America");
	s->cards[2] = create_card("Dr Strange");
	s->cards[3] = create_card("Iron Man");
	s->cards[4] = create_card("La Femme Invisible");
	s->cards[5] = create_card("Catwoman");
	s->cards[6] = create_card("Flash");
	s->cards[7] = create_card("Raven");
	s->cards[8] = create_card("Swamp Thing");
	s->cards[9] = create_card("Deathstroke");
	s->cards[10] = create_card("Green Lantern");
	s->cards[11] = create_card("Batman");
}
