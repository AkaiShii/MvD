
#include "game.h"

char *ev_text_entered(game *s, char *str, sfEvent ev)
{
	int i = 0;

	while (str[i])
		i++;
	switch (ev.type) {
	case sfEvtClosed:
		s->entered = 0;
		sfRenderWindow_close(s->window);
		break;
	case sfEvtKeyReleased:
		if (ev.key.code == sfKeyReturn)
			s->entered = 0;
		break;
	case sfEvtTextEntered:
		if (i < 50 && ev.text.unicode >= 32 && ev.text.unicode < 127)
			str[i] = ev.text.unicode;
		else if (sfKeyboard_isKeyPressed(sfKeyBack))
			str[i - 1] = '\0';
		break;
	default:
		break;
	}
	return (str);
}

char *text_entered(game *s)
{
	char *str = calloc(1, 50);
	sfEvent ev;

	s->entered = 1;
	while (s->entered) {
		while (sfRenderWindow_pollEvent(s->window, &ev))
			str = ev_text_entered(s, str, ev);
		sfRenderWindow_clear(s->window, sfWhite);
		text(s, "Enter text:", (sfVector2f){700, 200}, sfBlack);
		text(s, str, (sfVector2f){700, 400}, sfBlack);
		sfRenderWindow_display(s->window);
	}
	return (str);
}
