/*
** EPITECH PROJECT, 2018
** my_rpg
** File description:
** functions
*/

#include "game.h"

char *get_texture(char *name)
{
	int c = 0;
	int lname = my_strlen(name);
	char *path = "picture/";
	char *final = malloc(sizeof(char) * (9 + lname));

	for (int i = 0; i < 8; i++) {
		final[c] = path[i];
		c++;
	}
	for (int i = 0; i < lname; i++) {
		final[c] = name[i];
		c++;
	}
	final[c] = '\0';
	return (final);
}

sprite create_sprite(char *name, int x, int y)
{
	sprite new;
	
	new.sprite = sfSprite_create();
	new.text = sfTexture_createFromFile(get_texture(name), NULL);
	new.pos.x = x;
	new.pos.y = y;
	sfSprite_setTexture(new.sprite, new.text, sfTrue);
	sfSprite_setPosition(new.sprite, new.pos);
	return (new);
}

/*view create_view(float left, float top, float width, float height)
{
	view new;

	new.rect.top = top;
	new.rect.left = left;
	new.rect.width = width;
	new.rect.height = height;
	new.view = sfView_createFromRect(new.rect);
	return (new);
	}*/

void destroy(sprite *new)
{
	sfTexture_destroy(new->text);
	sfSprite_destroy(new->sprite);
}

int mouse(game *s, sfVector2f pos, int x, int y)
{
	sfVector2i ms = sfMouse_getPositionRenderWindow(s->window);

	if (ms.x > pos.x && ms.x < pos.x + x
	    && ms.y > pos.y && ms.y < pos.y + y)
		return (1);
	return (0);
}

/*void text(game *s, char *str, sfVector2f pos, sfColor color)
{
	sfText *new = sfText_create();

	sfText_setString(new, str);
	sfText_setCharacterSize(new, 25);
	sfText_setFont(new, s->font);
	sfText_setColor(new, color);
	sfText_setCharacterSize(new, 22);
	sfText_setPosition(new, pos);
	sfRenderWindow_drawText(s->window, new, NULL);
	}*/

sfIntRect create_rect(int top, int left, int height, int width)
{
	sfIntRect rect;

	rect.top = top;
	rect.left = left;
	rect.height = height;
	rect.width = width;
	return (rect);
}

button create_button(char *name, int x, int y)
{
	button new;
	sfVector2u size;

	new.art = create_sprite(name, x, y);
	size = sfTexture_getSize(new.art.text);
	new.x = size.x;
	new.y = size.y;
	new.art.rect = create_rect(0, 0, size.y, size.x);
	sfSprite_setTextureRect(new.art.sprite, new.art.rect);
	return (new);
}

void draw(game *s, sprite new)
{
	sfRenderWindow_drawSprite(s->window, new.sprite, NULL);
}
