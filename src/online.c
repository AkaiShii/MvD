
#include "game.h"

void init_lobby(game *s)
{
	s->o.send = sfPacket_create();
	s->o.received = sfPacket_create();
	s->o.btn = malloc(sizeof(button) * 2);
	s->o.btn[0] = create_button("button/créer_partie.png", 100, 200);
	s->o.btn[1] = create_button("button/join.png", 100, 300);
	s->o.back = create_sprite("interface/lobby.png", 0, 0);
}

char *receive_packet(game *s)
{
	sfSocketStatus stat;

	sfPacket_clear(s->o.received);
	stat = sfTcpSocket_receivePacket(s->o.server, s->o.received);
	if (stat != sfSocketDone)
		receive_packet(s);
	return ((char *)sfPacket_getData(s->o.received));
}

int send_packet(game *s, char *data)
{
	sfSocketStatus stat;

	sfPacket_append(s->o.send, data, sizeof(data) + strlen(data) + 1);
	stat = sfTcpSocket_sendPacket(s->o.client, s->o.send);
	sfPacket_clear(s->o.send);
	if (stat == sfSocketDone)
		return (0);
	return (1);
}

void client(game *s)
{
	char *ip = text_entered(s);

	s->o.ip = sfIpAddress_fromString(ip);
	s->o.client = sfTcpSocket_create();
	sfRenderWindow_clear(s->window, sfBlack);
	draw(s, s->o.back);
	if (sfTcpSocket_connect(s->o.client, s->o.ip, 4242, sfSeconds(60)) == sfSocketDone) {
		s->o.ip = sfIpAddress_getLocalAddress();
		sfIpAddress_toString(s->o.ip, ip);
		send_packet(s, ip);
		s->o.listen = sfTcpListener_create();
		s->o.server = sfTcpSocket_create();
		sfTcpListener_listen(s->o.listen, 8080, s->o.ip);
		if (sfTcpListener_accept(s->o.listen, &s->o.server) == sfSocketDone)
			text(s, "Connexion reussi !", (sfVector2f){700, 300}, sfWhite);
	} else {
		text(s, "Connexion echouee.", (sfVector2f){700, 300}, sfWhite);
		return;
	}
	sfRenderWindow_display(s->window);
	free(ip);
	sleep(2);
	sfTcpListener_destroy(s->o.listen);
	s->lobby = 0;
	s->p.turn = 2;
	game_loop(s);
}

void server(game *s)
{
	char *ip = calloc(1, 20);

	s->o.listen = sfTcpListener_create();
	s->o.server = sfTcpSocket_create();
	s->o.ip = sfIpAddress_getLocalAddress();
	sfIpAddress_toString(s->o.ip, ip);
	sfTcpListener_setBlocking(s->o.listen, sfFalse);
	sfTcpListener_listen(s->o.listen, 4242, s->o.ip);
	while (42) {
		if (sfKeyboard_isKeyPressed(sfKeyEscape))
			return;
		if (sfTcpListener_accept(s->o.listen, &s->o.server) == sfSocketDone)
			break;
		sfRenderWindow_clear(s->window, sfBlack);
		draw(s, s->o.back);
		text(s, "En attente d'un joueur...", (sfVector2f){700, 300}, sfWhite);
		text(s, ip, (sfVector2f){700, 400}, sfWhite);
		sfRenderWindow_display(s->window);
	}
	sfRenderWindow_clear(s->window, sfBlack);
	draw(s, s->o.back);
	ip = (char *)receive_packet(s);
	s->o.client = sfTcpSocket_create();
	s->o.ip = sfIpAddress_fromString(ip);
	if (sfTcpSocket_connect(s->o.client, s->o.ip, 8080, sfSeconds(60)) == sfSocketDone)
		text(s, "Connexion reussi !", (sfVector2f){700, 300}, sfWhite);
	else {
		text(s, "Connexion echouee.", (sfVector2f){700, 300}, sfWhite);
		return;
	}
	sfRenderWindow_display(s->window);
	sleep(2);
	sfTcpListener_destroy(s->o.listen);
	s->lobby = 0;
	s->p.turn = 1;
	game_loop(s);
}

void draw_lobby_button(game *s, int i)
{
	if (mouse(s, s->o.btn[i].art.pos, s->o.btn[i].x, s->o.btn[i].y)) {
		if (sfMouse_isButtonPressed(sfMouseLeft))
			s->o.btn[i].art.rect.left = s->o.btn[i].x * 2;
		else
			s->o.btn[i].art.rect.left = s->o.btn[i].x;
	} else
		s->o.btn[i].art.rect.left = 0;
	sfSprite_setTextureRect(s->o.btn[i].art.sprite, s->o.btn[i].art.rect);
	draw(s, s->o.btn[i].art);
}

void draw_lobby(game *s)
{
	draw(s, s->o.back);
	for (int i = 0; i < 2; i++)
		draw_lobby_button(s, i);
}

void lobby_button(game *s, sfEvent ev)
{
	if (ev.mouseButton.button != sfMouseLeft)
		return;
	if (mouse(s, s->o.btn[0].art.pos, s->o.btn[0].x, s->o.btn[0].y))
		server(s);
	if (mouse(s, s->o.btn[1].art.pos, s->o.btn[1].x, s->o.btn[1].y))
		client(s);
}

void ev_lobby(game *s)
{
	sfEvent ev;

	if (sfKeyboard_isKeyPressed(sfKeyEscape))
		s->lobby = 0;
	while (sfRenderWindow_pollEvent(s->window, &ev)) {
		switch (ev.type) {
		case sfEvtClosed:
			s->lobby = 0;
			sfRenderWindow_close(s->window);
			break;
		case sfEvtMouseButtonReleased:
			lobby_button(s, ev);
			break;
		default:
			break;
		}
	}
}

void lobby(game *s)
{
	init_lobby(s);
	s->lobby = 1;
	while (s->lobby) {
		ev_lobby(s);
		sfRenderWindow_clear(s->window, sfBlack);
		draw_lobby(s);
		sfRenderWindow_display(s->window);
	}
}
