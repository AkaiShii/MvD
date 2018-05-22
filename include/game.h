#ifndef GAME_H_
#define GAME_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <SFML/Network.h>
#include <SFML/System/Time.h>
#include <stddef.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>

//Effets: Vélocité/Première Ligne/Assaut/Sacrifice/Camouflage/Execution/Combat

typedef struct sprite
{
	sfSprite *sprite;
	sfTexture *text;
	sfVector2f pos;
	sfIntRect rect;
	sfClock *clock;
	int i;
	int c;
} sprite;

typedef struct view
{
	sfView *view;
	sfFloatRect rect;
} view;

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
	int spell;
	int id;
	int rare;
	int atk;
	int hp;
	int unit;
	int mana;
	int *effet;
	int play;
	sfMusic *summon;
	sfMusic *mtype;
} card;

typedef struct player
{
	card *deck;
	card *main;
	card *cime;
	card *board;
	int c_deck;
	int c_cime;
	int c_main;
	int hp;
	int unit;
	int next;
} player;

typedef struct account
{
	char *name;
	char *titre;
	sprite icon;
	card *collection;
	int cards;
	int gold;
	int deck;
} account;

typedef struct animation
{
	sprite expl;
	sprite fairy;
	sprite wind;
	sprite hit;
	sprite preload;
	sprite expl_y;
	sprite explosion;
	sprite spirale;
	sprite iceball;
	sprite flocon;
	sprite plasma;
	sprite magic;
	sprite circlefire;
	sprite earth;
	sprite light;
} animations;

typedef struct menu
{
	sfClock *c_anim;
	sfMusic *marvel;
	sfMusic *dc;
	sprite b_btn;
	sprite back;
	button *btn;
} menu;

typedef struct play
{
	sprite back;
	int turn;
	int turns;
	player j1;
	player j2;
} play;

typedef struct online
{
	sprite back;
	button *btn;
	sfTcpSocket *client;
	sfTcpSocket *server;
	sfTcpListener *listen;
	sfIpAddress ip;
	sfPacket *send;
	sfPacket *received;
} online;

typedef struct game
{
	animations a;
	online o;
	menu m;
	play p;
	int play;
	int lobby;
	int entered;
	sfRenderWindow *window;
	sfFont *font;
	account c;
	card *cards;
} game;

sprite create_sprite(char *, int, int);
button create_button(char *, int, int);
view create_view(float, float, float, float);
void destroy(sprite *);
int mouse(game *, sfVector2f, int, int);
void text(game *, char *, sfVector2f, sfColor);
void draw(game *, sprite);
sfIntRect create_rect(int, int, int, int);
char *receive_packet(game *);
int send_packet(game *, char *);

void melanger(game *);
card *load_deck(char *);
card create_card(char *);
card verso(int, int);
card copy_card(card);

int animation(game *, sprite *, sfVector2f, int, int);

int check_account(void);
void create_account(game *);
void load_account(game *);
void save_account(game *);
void init_cards(game *);
void init_animations(game *);

void first_draw(game *);
void draw_card(player *, int);
void buff_stat(game *, int, int);
void buff_effet(game *, int);
void destroy_card(game *);
void aoe(game *, int, int);
void damage(game *, int);

int get_target(game *);
void use_effect(game *, int);
void die(game *, card);
void summon(game *, int);
void attack(game *, int);
void summon_j2(game *);
void attack_j2(game *);
void draw_anim(game *);
void launch_menu(game *);
void lobby(game *);
void game_loop(game *);

char *int_to_char(int);
char *text_entered(game *);
char *my_strcpy(char const *);
char *my_strcpy_n(char const *);
char *my_strcat(char *, char const *);
int my_strlen(char const *);
int my_getnbr(char *);

#endif
