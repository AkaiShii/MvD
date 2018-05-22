
#include "game.h"

player init_player(char *deck)
{
	player new;

	new.hp = 30;
	new.unit = 0;
	new.next = 0;
	new.c_deck = 28;
	new.c_cime = 0;
	new.c_main = 5;
	new.deck = load_deck(my_strcat("acc/", deck));
	new.main = malloc(sizeof(card) * 11);
	new.cime = malloc(sizeof(card) * 30);
	new.board = malloc(sizeof(card) * 11);
	for (int i = 0; i < 30; i++) {
		if (i < 11) {
			new.main[i].id = 0;
			new.board[i].id = 0;
		}
		new.cime[i].id = 0;
	}
	return (new);
}

player init_j2(void)
{
	player new;

	new.hp = 30;
	new.unit = 0;
	new.next = 0;
	new.c_deck = 28;
	new.c_cime = 0;
	new.c_main = 5;
	new.deck = malloc(sizeof(card) * 30);
	new.main = malloc(sizeof(card) * 11);
	new.cime = malloc(sizeof(card) * 30);
	new.board = malloc(sizeof(card) * 11);
	for (int i = 0; i < 30; i++) {
		if (i < 11) {
			new.main[i].id = 0;
			new.board[i].id = 0;
		}
		new.cime[i].id = 0;
		new.deck[i] = verso(0, 0);
	}
	return (new);
}

void draw_game(game *s)
{
	draw(s, s->p.back);
	for (int i = 0; i < 10; i++) {
		if (s->p.j1.main[i].id > 0)
			draw(s, s->p.j1.main[i].hand);
		if (s->p.j2.main[i].id > 0)
			draw(s, s->p.j2.main[i].hand);
		if (s->p.j1.board[i].id > 0)
			draw(s, s->p.j1.board[i].board);
		if (s->p.j2.board[i].id > 0)
			draw(s, s->p.j2.board[i].board);
	}
	text(s, "Tour", (sfVector2f){1750, 483}, sfWhite);
	text(s, int_to_char(s->p.turns), (sfVector2f){1830, 483}, sfWhite);
	text(s, int_to_char(s->p.j1.unit), (sfVector2f){200, 483}, sfWhite);
	text(s, int_to_char(s->p.j1.next), (sfVector2f){1700, 483}, sfWhite);
}

void draw_single_anim(game *s, sprite anim, sfVector2f p, int l, int f)
{
	while (42) {
		sfRenderWindow_clear(s->window, sfBlack);
		draw_game(s);
		if (animation(s, &anim, p, l, f) == 0)
			break;
		sfRenderWindow_display(s->window);
	}
}

void click_ev(game *s)
{
	for (int i = 0; i < 10; i++) {
		if (s->p.j1.main[i].id > 0 &&
		    mouse(s, s->p.j1.main[i].hand.pos, 165, 300)) {
			summon(s, i);
			return;
		} else if (s->p.j1.board[i].id > 0 && s->p.j1.board[i].play == 0 &&
			   mouse(s, s->p.j1.board[i].board.pos, 165, 300)) {
			printf("a\n");
			attack(s, i);
			return;
		}
	}
}

void ev_game(game *s)
{
	sfEvent ev;

	while (sfRenderWindow_pollEvent(s->window, &ev)) {
		switch (ev.type) {
		case sfEvtClosed:
			s->play = 0;
			s->p.turn = 0;
			sfRenderWindow_close(s->window);
			break;
		case sfEvtMouseButtonReleased:
			click_ev(s);
			break;
		case sfEvtKeyReleased:
			if (ev.key.code == sfKeyEscape) {
				s->p.turn = 2;
				send_packet(s, "End");
			}
			break;
		default:
			break;
		}
	}
}

void check_action(game *s, char *action)
{
	if (!strcmp(action, "Invoquer"))
		summon_j2(s);
	if (!strcmp(action, "Attaque"))
		attack_j2(s);
	if (!strcmp(action, "End"))
		s->p.turn = 1;
}

void en_turn(game *s)
{
	char *action = NULL;

	s->p.turns++;
	draw_card(&s->p.j2, 0);
	while (s->p.turn == 2) {
		sfRenderWindow_clear(s->window, sfBlack);
		draw_game(s);
		sfRenderWindow_display(s->window);
		action = (char *)receive_packet(s);
		check_action(s, action);
	}
}

void my_turn(game *s)
{
	s->p.turns++;
	s->p.j1.unit++;
	s->p.j1.unit += s->p.j1.next;
	s->p.j1.next = 0;
	draw_card(&s->p.j1, 1);
	while (s->p.turn == 1) {
		ev_game(s);
		sfRenderWindow_clear(s->window, sfBlack);
		draw_game(s);
		sfRenderWindow_display(s->window);
	}
	s->p.j1.next += s->p.j1.unit;
	for (int i = 0; i < 10; i++)
		if (s->p.j1.board[i].id > 0 && s->p.j1.board[i].play > 0)
			s->p.j1.board[i].play--;
}

void game_loop(game *s)
{
	s->p.j1 = init_player("test");
	s->p.j2 = init_j2();
	melanger(s);
	first_draw(s);
	s->p.back = create_sprite("interface/b_game.jpg", 0, 0);
	s->p.turns = 0;
	s->play = 1;
	while (s->play) {
		ev_game(s);
		sfRenderWindow_clear(s->window, sfBlack);
		draw_game(s);
		sfRenderWindow_display(s->window);
		if (s->p.turn == 1)
			my_turn(s);
		else
			en_turn(s);
	}
}
