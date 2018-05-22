
#include "game.h"

void destroy_account(game *s)
{
	if (s->c.name != NULL)
		free(s->c.name);
	if (s->c.titre != NULL)
		free(s->c.titre);
}

int main(void)
{
	game s;
	sfVideoMode v = {1920, 967, 32};

	s.window = sfRenderWindow_create(v, "Marvel vs DC", sfDefaultStyle, NULL);
	srand(time(NULL));
	if (check_account())
		create_account(&s);
	else
		load_account(&s);
	s.font = sfFont_createFromFile("picture/cooprblk.ttf");
	//init_cards(&s);
	launch_menu(&s);
	destroy_account(&s);
	sfRenderWindow_destroy(s.window);
	return (0);
}
