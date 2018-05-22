
#include "game.h"

void client(void)
{
	sfTime time = sfSeconds(1000000);
	sfTcpSocket *socket = sfTcpSocket_create();
	sfIpAddress ip;
	//sfIpAddress ip = sfIpAddress_getLocalAddress();
	//sfIpAddress ip = sfIpAddress_getPublicAddress(time);
	//sfIpAddress ip = sfIpAddress_fromString("192.168.122.1, 55001");

        if (sfTcpSocket_connect(socket, ip, 55001, time) == sfSocketDone)
		printf("Connected\n");
}

void server(void)
{
	sfTcpListener *listen = sfTcpListener_create();
	sfTcpSocket *socket = sfTcpSocket_create();
	sfIpAddress ip = sfIpAddress_getLocalAddress();

	sfTcpListener_listen(listen, 55001, ip);
	if (sfTcpListener_accept(listen, &socket) == sfSocketDone)
		printf("Connected\n");
}

int main(void)
{
	size_t len = 0;
	char *buffer = calloc(1, 1);

	printf("Enter s for Server, Enter c for client\n");
	getline(&buffer, &len, stdin);
	if (buffer[0] == 's')
		server();
	else if (buffer[0] == 'c')
		client();
}

























void socket_2(sfTcpSocket *socket)
{
	size_t received = 100;
	char *buffer = calloc(1, 100);
	char *buff = calloc(1, 1000);

	sfTcpSocket_receive(socket, buff, sizeof(buff), &received);
	printf("%s\n", buff);
	while (42) {
		write(0, "c\n", 2);
		if (sfTcpSocket_receive(socket, buff, sizeof(buff), &received) == sfSocketDone)
			printf("%s\n", buff);
		write(0, "b\n", 2);
		if (sfKeyboard_isKeyPressed(sfTrue)) {
			write(0, "a\n", 2);
			read(0, buffer, 100);
			sfTcpSocket_send(socket, buffer, strlen(buffer));
		}
	}
}

void socket_1(sfTcpSocket *socket)
{
	size_t received = 100;
	char *buffer = calloc(1, 100);
	char *buff = calloc(1, 1000);

	sfTcpSocket_receive(socket, buff, sizeof(buff), &received);
	printf("%s\n", buff);
	while (42) {
		if (sfTcpSocket_receive(socket, buff, sizeof(buff), &received) == sfSocketDone)
			printf("%s\n", buff);
		if (sfKeyboard_isKeyPressed(sfTrue)) {
			read(0, buffer, 100);
			sfTcpSocket_send(socket, buffer, strlen(buffer));
		}
	}
}

void server(sfTcpSocket *socket1, sfIpAddress ip1, unsigned short port)
{
	sfIpAddress ip = sfIpAddress_getLocalAddress();
	sfTcpSocket *socket = sfTcpSocket_create();
	sfTcpListener *listen = sfTcpListener_create();

        printf("Ok\n");
	if (sfTcpListener_listen(listen, 4242, ip1) == sfSocketError)
		server(socket, ip1, port + 1);
	printf("Ok2\n");
	sfTcpListener_accept(listen, &socket);
	printf("New client connected.\n");
}

int client(sfTcpSocket *socket1, unsigned short port)
{
	sfTcpSocket *socket = sfTcpSocket_create();
	sfIpAddress ip = sfIpAddress_getLocalAddress();
	//sfIpAddress ip;
	sfTime time = sfSeconds(1000);
	char *address = calloc(1, 9);
	size_t len = 0;
       	sfSocketStatus s;
	
	printf("%d\nIP: ", port);
	getline(&address, &len, stdin);
	ip = sfIpAddress_fromString(address);
	s = sfTcpSocket_connect(socket, ip, 4242, time);
	if (s == sfSocketDone) {
		printf("Connected\n");
		return (1);
	}
	if (s == sfSocketError)
		printf("OK\n");
	if (s == sfSocketPartial)
		printf("Par\n");
	if (s == sfSocketDisconnected)
		printf("Deco\n");
	if (s == sfSocketNotReady)
		printf("Not\n");
	sfIpAddress_toString(ip, address);
	printf("%s\n",  address);
	return (0);
}

int main(void)
{
	//sfTime time = sfSeconds(10);
	//sfIpAddress ip = sfIpAddress_getPublicAddress(time);
	sfIpAddress ip = sfIpAddress_getLocalAddress();
	sfTcpSocket *socket = sfTcpSocket_create();
	size_t len = 0;
	char *address = calloc(1, 9);
	char *buffer = calloc(1, 1);

	sfIpAddress_toString(ip, address);
	printf("%s\n", address);
	printf("Enter s for Server, Enter c for client\n");
	getline(&buffer, &len, stdin);
	if (buffer[0] == 's')
		server(socket, ip, 2000);
	else if (buffer[0] == 'c')
		client(socket, 2000);
	sfTcpSocket_disconnect(socket);
	return (0);
	}
