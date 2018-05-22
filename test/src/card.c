
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
	new.id = src.id;
	new.atk = src.atk;
	new.hp = src.hp;
	new.unit = src.unit;
	new.mana = src.mana;
	return (new);
}

card create_card(char *name, int info[])
{
	card new;

	new.name = my_strcpy(name);
	new.hand = create_sprite(my_strcat(name, ".png"), 0, 0);
	new.id = info[0];
	new.atk = info[1];
	new.hp = info[2];
	new.unit = info[3];
	new.mana = info[4];
	return (new);
}

void init_cards(game *s)
{
	s->cards = malloc(sizeof(card) * 5);
	s->cards[0] = create_card("Dr Strange", (int[5]){1, 6, 7, 6, 8});
	s->cards[1] = create_card("Iron Man", (int[5]){2, 3, 2, 1, 2});
	s->cards[2] = create_card("La Femme Invisible", (int[5]){3, 4, 4, 6, 5});
	s->cards[3] = create_card("Luke Cage", (int[5]){4, 3, 6, 5, 4});
	s->cards[4] = create_card("Spiderman", (int[5]){5, 8, 8, 6, 8});
}
