#include <SFML/Network/Types.h>
#include <SFML/Network/IpAddress.h>
#include <SFML/Network/Export.h>
#include <SFML/Network/SocketStatus.h>
#include <SFML/System/Time.h>
#include <stddef.h>
#include "game.h"

int main(int ac, char **av)
{
	sfTcpSocket *socket = sfTcpSocket_create();
	//sfIpAddress ip = sfTcpSocket_getRemoteAddress(socket);
}
