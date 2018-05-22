
#include "game.h"

void use_effect(game *s, int id)
{
	switch (id) {
	case 10:
		break;
	case 3:
		aoe(s, 2, 2);
		break;
	default:
		break;
	}
}
