
#include "game.h"

void destroy_menu(game *s)
{
	for (int i = 0; i < 4; i++)
		destroy(&s->m.btn[i].art);
	free(s->m.btn);
	destroy(&s->m.back);
	sfMusic_destroy(s->m.marvel);
	sfMusic_destroy(s->m.dc);
}

void init_menu(game *s)
{
	s->m.btn = malloc(sizeof(button) * 4);
	s->m.btn[0] = create_button("button/jouer.png", 100, 200);
	s->m.btn[1] = create_button("button/deck.png", 100, 300);
	s->m.btn[2] = create_button("button/collection.png", 100, 400);
	s->m.btn[3] = create_button("button/quitter.png", 100, 500);
	s->m.marvel = sfMusic_createFromFile("song/Avengers.ogg");
	s->m.dc = sfMusic_createFromFile("song/Justice League.ogg");
	s->m.back = create_sprite("interface/backmvd.png", 0, 0);
	s->m.b_btn = create_sprite("interface/b_btn.jpg", 50, 100);

}

void draw_menu_button(game *s, int i)
{
	if (mouse(s, s->m.btn[i].art.pos, s->m.btn[i].x, s->m.btn[i].y)) {
		if (sfMouse_isButtonPressed(sfMouseLeft))
			s->m.btn[i].art.rect.left = s->m.btn[i].x * 2;
		else
			s->m.btn[i].art.rect.left = s->m.btn[i].x;
	} else
		s->m.btn[i].art.rect.left = 0;
	sfSprite_setTextureRect(s->m.btn[i].art.sprite, s->m.btn[i].art.rect);
	draw(s, s->m.btn[i].art);
}

void draw_menu(game *s)
{
	//draw(s, s->m.back);
	draw_anim(s);
	draw(s, s->m.b_btn);
	for (int i = 0; i < 4; i++)
		draw_menu_button(s, i);
	text(s, s->c.name, (sfVector2f){1700, 100}, sfWhite);
	text(s, s->c.titre, (sfVector2f){1670, 150}, sfWhite);
	text(s, int_to_char(s->c.gold), (sfVector2f){1650, 200}, sfYellow);
}

void menu_buttons(game *s, sfEvent ev)
{
	if (ev.mouseButton.button != sfMouseLeft)
		return;
	if (mouse(s, s->m.btn[0].art.pos, s->m.btn[0].x, s->m.btn[0].y))
		lobby(s);
	if (mouse(s, s->m.btn[3].art.pos, s->m.btn[3].x, s->m.btn[3].y))
		sfRenderWindow_close(s->window);
}

void ev_menu(game *s)
{
	sfEvent ev;

	while (sfRenderWindow_pollEvent(s->window, &ev)) {
		switch (ev.type) {
		case sfEvtClosed:
			sfRenderWindow_close(s->window);
			break;
		case sfEvtMouseButtonReleased:
			menu_buttons(s, ev);
			break;
		default:
			break;
		}
	}
}

void rand_menu_song(game *s)
{
	int r = rand() % 2;

	if (r == 0)
		sfMusic_play(s->m.marvel);
	else
		sfMusic_play(s->m.dc);
}

void menu_song(game *s)
{
	static int bool = 0;

	if (sfMusic_getStatus(s->m.dc) == sfPlaying)
		bool = 1;
	else if (sfMusic_getStatus(s->m.marvel) == sfPlaying)
		bool = 2;
	if (sfMusic_getStatus(s->m.dc) == sfStopped && bool == 1)
		sfMusic_play(s->m.marvel);
	else if (sfMusic_getStatus(s->m.marvel) == sfStopped && bool == 2)
		sfMusic_play(s->m.dc);
}

void launch_menu(game *s)
{
	init_menu(s);
	init_animations(s);
	s->m.c_anim = sfClock_create();
	//rand_menu_song(s);
	while (sfRenderWindow_isOpen(s->window)) {
		//menu_song(s);
		ev_menu(s);
		sfRenderWindow_clear(s->window, sfBlack);
		draw_menu(s);
		sfRenderWindow_display(s->window);
	}
	destroy_menu(s);
}
