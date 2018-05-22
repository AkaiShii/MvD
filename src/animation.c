
#include "game.h"

int animation(game *s, sprite *anim, sfVector2f pos, int line, int frame)
{
	sfTime time = sfClock_getElapsedTime(anim->clock);
        float second = time.microseconds / 1000000.0;
	sfVector2u size = sfTexture_getSize(anim->text);
	sfIntRect rect = create_rect(size.y / line * anim->c, size.x / frame * anim->i,
				     size.y / line, size.x / frame);

	if (anim->i == 0 && anim->c == 0)
		sfSprite_setTextureRect(anim->sprite, rect);
	if (anim->i == frame) {
		rect.left = 0;
		anim->i = 0;
		anim->c++;
	}
	if (anim->c == line) {
		anim->c = 0;
		return (0);
	}
	if (second >= 0.05) {
		sfSprite_setTextureRect(anim->sprite, rect);
		sfClock_restart(anim->clock);
		anim->i++;
	}
	sfSprite_setPosition(anim->sprite, pos);
	sfRenderWindow_drawSprite(s->window, anim->sprite, NULL);
	return (1);
}

void init_animations(game *s)
{
		s->a.fairy = create_sprite("animation/fairy_explosion.png", 0, 0);
	s->a.wind = create_sprite("animation/green_tornade.png", 0, 0);
	s->a.hit = create_sprite("animation/hit_green.png", 0, 0);
	s->a.expl = create_sprite("animation/expl.png", 0, 0);
	s->a.preload = create_sprite("animation/preload.png", 0, 0);
	s->a.expl_y = create_sprite("animation/expl_y.png", 0, 0);
	s->a.explosion = create_sprite("animation/explosion.png", 0, 0);
	s->a.spirale = create_sprite("animation/spirale.png", 0, 0);
	s->a.iceball = create_sprite("animation/iceball.png", 0, 0);
	s->a.flocon = create_sprite("animation/flocon.png", 0, 0);
	s->a.magic = create_sprite("animation/magic.png", 0, 0);
	s->a.plasma = create_sprite("animation/plasma.png", 0, 0);
	s->a.circlefire = create_sprite("animation/circlefire.png", 0, 0);
	s->a.earth = create_sprite("animation/earth.png", 0, 0);
	s->a.light = create_sprite("animation/light.png", 0, 0);
}

void draw_anim(game *s)
{
	animation(s, &s->a.expl, (sfVector2f){530, 200}, 6, 5);
	animation(s, &s->a.wind, (sfVector2f){680, 200}, 6, 5);
	animation(s, &s->a.hit, (sfVector2f){850, 200}, 5, 5);
	animation(s, &s->a.fairy, (sfVector2f){530, 0}, 8, 8);
	animation(s, &s->a.preload, (sfVector2f){680, 0}, 5, 5);
	animation(s, &s->a.expl_y, (sfVector2f){850, 0}, 6, 5);
	animation(s, &s->a.explosion, (sfVector2f){1000, 0}, 8, 5);
	animation(s, &s->a.spirale, (sfVector2f){1150, 0}, 7, 5);
	animation(s, &s->a.iceball, (sfVector2f){1300, 0}, 5, 5);
	animation(s, &s->a.flocon, (sfVector2f){1450, 0}, 4, 5);
	animation(s, &s->a.plasma, (sfVector2f){1600, 0}, 5, 5);
	animation(s, &s->a.circlefire, (sfVector2f){1750, 0}, 5, 5);
	animation(s, &s->a.magic, (sfVector2f){530, 400}, 6, 5);
	animation(s, &s->a.earth, (sfVector2f){1000, 400}, 4, 5);
	animation(s, &s->a.light, (sfVector2f){800, 400}, 8, 5);
}
