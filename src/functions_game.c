
#include "game.h"

int check_effet(card carte, int effet)
{
	for (int c = 0; c < carte.spell; c++)
		if (carte.effet[c] == effet)
			return (1);
	return (0);
}

void first_draw(game *s)
{
	s->p.j1.main[0] = copy_card(s->p.j1.deck[29]);
	s->p.j1.main[0].hand.pos.x = 500;
	s->p.j1.main[0].hand.pos.y = 750;
	sfSprite_setPosition(s->p.j1.main[0].hand.sprite, s->p.j1.main[0].hand.pos);
	s->p.j1.deck[29].id = 0;
	s->p.j2.main[0] = verso(500, -100);
	for (int i = 1; i < 5; i++) {
		s->p.j1.main[i] = copy_card(s->p.j1.deck[s->p.j1.c_deck]);
		s->p.j1.main[i].hand.pos.x = s->p.j1.main[i - 1].hand.pos.x + 150;
		s->p.j1.main[i].hand.pos.y = 750;
		sfSprite_setPosition(s->p.j1.main[i].hand.sprite, s->p.j1.main[i].hand.pos);
		s->p.j1.deck[s->p.j1.c_deck].id = 0;
		s->p.j1.c_deck--;
		s->p.j2.main[i] = verso(s->p.j2.main[i - 1].hand.pos.x + 150, -100);
		s->p.j2.c_deck--;
	}
}

int click_target(game *s, int taunt)
{
	for (int i = 0; i < 10; i++)
		if (taunt > 0 && mouse(s, s->p.j2.board[i].board.pos, 215, 300) &&
		    check_effet(s->p.j2.board[i], 2) && !check_effet(s->p.j2.board[i], 5))
			return (i);
		else if (taunt == 0 && mouse(s, s->p.j2.board[i].board.pos, 215, 300) &&
			 !check_effet(s->p.j2.board[i], 5))
			return (i);
	return (11);
}

int get_target(game *s)
{
	sfEvent ev;
	int taunt = 0;

	for (int i = 0; i < 10; i++)
		if (s->p.j2.board[i].id > 0 &&
		    check_effet(s->p.j2.board[i], 2))
			taunt++;
	while (sfRenderWindow_pollEvent(s->window, &ev)) {
		switch (ev.type) {
		case sfEvtClosed:
			s->play = 0;
			s->p.turn = 0;
			sfRenderWindow_close(s->window);
			return (10);
		case sfEvtMouseButtonReleased:
		        return (click_target(s, taunt));
		case sfEvtKeyReleased:
			if (ev.key.code == sfKeyEscape)
				return (10);
			break;
		default:
			break;
		}
	}
	return (11);
}

void die(game *s, card carte)
{
	//draw_single_anim(s, s->a.explosion, s->p.j1.board[c].board.pos, 8, 5);
	//if (check_effet(carte, 4))
	//	sacrifice();
}

void attack_j2(game *s)
{
	int c = my_getnbr(receive_packet(s));
	int target = my_getnbr(receive_packet(s));

	if (check_effet(s->p.j1.board[c], 7))
		use_effect(s, s->p.j1.board[c].id);
	if (check_effet(s->p.j2.board[target], 7))
		use_effect(s, s->p.j2.board[target].id);
	s->p.j1.board[target].hp -= s->p.j2.board[c].atk;
	s->p.j2.board[c].hp -= s->p.j1.board[target].atk;
	//draw_single_anim(s, s->a.spirale, s->p.j2.board[target].board.pos, 7, 5);
	if (s->p.j1.board[target].hp <= 0 || check_effet(s->p.j2.board[c], 6)) {
		die(s, s->p.j1.board[target]);
		s->p.j1.board[target].id = 0;
	}
	if (s->p.j2.board[c].hp <= 0 || check_effet(s->p.j1.board[target], 6)) {
		die(s, s->p.j2.board[c]);
		s->p.j2.board[c].id = 0;
	}
}

void attack(game *s, int c)
{
	int target = 11;

	while (target > 10)
		target = get_target(s);
	if (target == 10)
		return;
	if (check_effet(s->p.j1.board[c], 7))
		use_effect(s, s->p.j1.board[c].id);
	if (check_effet(s->p.j2.board[target], 7))
		use_effect(s, s->p.j2.board[target].id);
	s->p.j1.board[c].hp -= s->p.j2.board[target].atk;
	s->p.j2.board[target].hp -= s->p.j1.board[c].atk;
	send_packet(s, "Attaque");
	send_packet(s, int_to_char(c));
	send_packet(s, int_to_char(target));
	//draw_single_anim(s, s->a.spirale, s->p.j2.board[target].board.pos, 7, 5);
	if (s->p.j1.board[c].hp <= 0 || check_effet(s->p.j2.board[target], 6)) {
		die(s, s->p.j1.board[c]);
		s->p.j1.board[c].id = 0;
	}
	if (s->p.j2.board[target].hp <= 0 || check_effet(s->p.j1.board[c], 6)) {
		die(s, s->p.j2.board[target]);
		s->p.j2.board[target].id = 0;
	}
	s->p.j1.board[c].play++;
}

void summon_j2(game *s)
{
	int i = 0;
	int c = 0;
	char *name = receive_packet(s);

	while (s->p.j2.board[i].id != 0) {
		if (i == 10)
			return;
		i++;
	}
	while (s->p.j2.main[c].id != 0) {
		if (c == 10)
			break;
		c++;
	}
	s->p.j2.main[c - 1].id = 0;
	s->p.j2.board[i] = create_card(name);
	//sfMusic_play(s->p.j2.board[i].summon);
	//sfMusic_play(s->p.j2.board[i].mtype);
	s->p.j2.board[i].board.pos.x = 450 + i * 200;
	s->p.j2.board[i].board.pos.y = 210;
	sfSprite_setPosition(s->p.j2.board[i].board.sprite, s->p.j2.board[i].board.pos);
	//draw_single_anim(s, s->a.spirale, s->p.j2.board[target].board.pos, 7, 5);
}

void summon(game *s, int c)
{
	int i = 0;

	while (s->p.j1.board[i].id != 0) {
		if (i == 10)
			return;
		i++;
	}
	if (s->p.j1.unit < s->p.j1.main[c].mana)
		return;
	s->p.j1.unit -= s->p.j1.main[c].mana;
	s->p.j1.next += s->p.j1.main[c].unit;
	s->p.j1.board[i] = copy_card(s->p.j1.main[c]);
	//sfMusic_play(s->p.j1.board[i].summon);
	//sfMusic_play(s->p.j1.board[i].mtype);
	while (c < 10) {
		if (s->p.j1.main[c + 1].id > 0) {
			s->p.j1.main[c] = copy_card(s->p.j1.main[c + 1]);
			s->p.j1.main[c].hand.pos.x = 500 + c * 150;
			s->p.j1.main[c].hand.pos.y = 750;
			sfSprite_setPosition(s->p.j1.main[c].hand.sprite,
					     s->p.j1.main[c].hand.pos);
		} else
			s->p.j1.main[c].id = 0;
		c++;
	}
	s->p.j1.board[i].board.pos.x = 450 + i * 200;
	s->p.j1.board[i].board.pos.y = 390;
	sfSprite_setPosition(s->p.j1.board[i].board.sprite, s->p.j1.board[i].board.pos);
	if (check_effet(s->p.j1.board[i], 1))
		s->p.j1.board[i].play = 0;
	if (check_effet(s->p.j1.board[i], 3))
		use_effect(s, s->p.j1.board[i].id);
	send_packet(s, "Invoquer");
	printf("\n%s\n", s->p.j1.board[i].name);
	send_packet(s, s->p.j1.board[i].name);
	//draw_single_anim(s, s->a.spirale, s->p.j2.board[target].board.pos, 7, 5);
}
