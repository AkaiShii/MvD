
#include "game.h"

void draw_card(player *p, int c)
{
	int i = 0;

	while (p->main[i].id > 0) {
		if (i == 10) {
			p->c_deck--;
			return;
		}
		i++;
	}
	p->main[i] = copy_card(p->deck[p->c_deck]);
	p->main[i].hand.pos.x = 500 + i * 150;
	p->main[i].hand.pos.y = -100 + 850 * c;
	sfSprite_setPosition(p->main[i].hand.sprite, p->main[i].hand.pos);
	p->c_deck--;
}

void buff_stat(game *s, int atk, int hp)
{
	int target = 11;

	while (target > 10)
		target = get_target(s);
	if (target == 10)
		return;
	s->p.j1.board[target].atk += atk;
	s->p.j1.board[target].hp += hp;
}

void buff_effet(game *s, int effet)
{
	int i = 0;
	int *effets;
	int target = 11;

	while (target > 10)
		target = get_target(s);
	if (target == 10)
		return;
	effets = malloc(sizeof(int) * s->p.j1.board[target].spell);
	for (int i = 0; i < s->p.j1.board[target].spell; i++)
		effets[i] = s->p.j1.board[target].effet[i];
	s->p.j1.board[target].effet = malloc(sizeof(int) * s->p.j1.board[target].spell + 1);
	for (; i < s->p.j1.board[target].spell; i++)
		s->p.j1.board[target].effet[i] = effets[i];
	s->p.j1.board[target].effet[i] = effet;
}

void destroy_card(game *s)
{
	int target = 11;

	while (target > 10)
		target = get_target(s);
	if (target == 10)
		return;
	//draw_single_anim(s, s->a.explosion, s->p.j2.board[target].board.pos, 8, 5);
	s->p.j2.board[target].id = 0;
}

void aoe(game *s, int dmg, int bool)
{
	for (int i = 0; i < 10; i++) {
		if ((bool == 1 || bool == 3) && s->p.j1.board[i].id > 0) {
			s->p.j1.board[i].hp -= dmg;
			if (s->p.j1.board[i].hp <= 0) {
				die(s, s->p.j1.board[i]);
				s->p.j1.board[i].id = 0;
			}
		}
		if ((bool == 2 || bool == 3) && s->p.j2.board[i].id > 0) {
			s->p.j2.board[i].hp -= dmg;
			if (s->p.j2.board[i].hp <= 0) {
				die(s, s->p.j2.board[i]);
				s->p.j2.board[i].id = 0;
			}
		}
	}
}

void damage(game *s, int dmg)
{
	int target = 11;

	while (target > 10)
		target = get_target(s);
	if (target == 10)
		return;
	s->p.j2.board[target].hp -= dmg;
	if (s->p.j2.board[target].hp <= 0) {
		die(s, s->p.j2.board[target]);
		s->p.j2.board[target].id = 0;
	}
}

void heal(game *s, int heal)
{
	int target = 11;

	while (target > 10)
		target = get_target(s);
	if (target == 10)
		return;
	s->p.j2.board[target].hp += heal;
}
