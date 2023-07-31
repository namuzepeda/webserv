/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:57:06 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 20:57:06 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

short	Server::counter = 0;

Server::Server(ServerHandler *handler): handler(handler), port(0), serverSocket(0) {
	this->id = Server::counter++;
}

int Server::getPort(void) {
	return (this->port);
}

std::string	const &Server::getHost(void) const{
	return (this->host);
}

int	Server::getSocket(void) {
	return (this->serverSocket);
}

InitType Server::init(const std::vector<Server> &servers, int tryTimes) {
	Config *config =  this->handler->getConfig();

	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(config->asInt("listen"));
	inet_pton(AF_INET, config->get("host").c_str(), &socketAddr.sin_addr); //socketAddr.sin_addr.s_addr = INADDR_ANY; //0.0.0.0


	InitType type = BIND_ERROR;
	for(std::vector<Server>::const_iterator it = servers.begin(); (*it).id != this->id; it++) {
		Server server = *it;
		if(this->host == server.host && this->port == server.port) {
			this->serverSocket = server.serverSocket;
			return (SUCCESS);
		}
		while(tryTimes--)
		{
			this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
			if (serverSocket == -1) {
				type = SOCKET_ERROR;
				continue ;
			}

			int flags = fcntl(serverSocket, F_GETFL, 0);
			fcntl(this->serverSocket, F_SETFL, flags | O_NONBLOCK);

			if (bind(serverSocket, (struct sockaddr *) &socketAddr, sizeof(socketAddr)) == -1) {
				type = BIND_ERROR;
				close(serverSocket);
				continue ;
			}

			// Escuchar por conexiones entrantes
			if (listen(serverSocket, 5) == -1) {
				type = LISTENING_ERROR;
				close(serverSocket);
				continue ;
			}

			return (SUCCESS);
		}
	}
	return (type);
}

ServerHandler *Server::getHandler(void) {
	return (this->handler);
}


