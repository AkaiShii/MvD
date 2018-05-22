#ifndef GAME_H_
#define GAME_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <SFML/Network.h>
#include <SFML/System.h>
#include <stddef.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>

typedef struct sprite
{
	sfSprite *sprite;
	sfTexture *text;
	sfVector2f pos;
	sfIntRect rect;
} sprite;

typedef struct button
{
	sprite art;
	int x;
	int y;
} button;

typedef struct card
{
	sprite hand;
	sprite board;
	char *name;
	int id;
	int rare;
	int atk;
	int hp;
	int unit;
	int mana;
	int *effet;
	int play;
} card;

typedef struct player
{
	card *deck;
	card *main;
	card *cime;
	card *board;
	int hp;
	int unit;
	int next;
} player;

typedef struct menu
{
	sfMusic *marvel;
	sfMusic *dc;
	sprite back;
	button *btn;
} menu;

typedef struct game
{
	menu m;
	int play;
	sfRenderWindow *window;
	player j1;
	player j2;
	card *cards;
} game;

sprite create_sprite(char *, int, int);
button create_button(char *, int, int);
//view create_view(float, float, float, float);
void destroy(sprite *);
int mouse(game *, sfVector2f, int, int);
void text(game *, char *, sfVector2f, sfColor);
void draw(game *, sprite);
sfIntRect create_rect(int, int, int, int);

card create_card(char *, int[]);
card copy_card(card);

void init_cards(game *);

void launch_menu(game *);

char *my_strcpy(char const *);
char *my_strcat(char *, char const *);
int my_strlen(char const *);

#endif
