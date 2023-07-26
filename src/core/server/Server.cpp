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

#include "Server.hpp"
#include "ServerUtils.hpp"
#include <unistd.h>

short	Server::counter = 0;

Server::Server(const ServerHandler &handler): serverSocket(0) {
	this->handler = handler;
	this->id = Server::counter++;
}

InitType Server::test(int times) {
	return init(times);
}

InitType Server::init(int tryTimes) {
	Config *config = this->getHandler().getConfig();

	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(config->asInt("listen"));
	inet_pton(AF_INET, config->get("host").c_str(), &socketAddr.sin_addr); //socketAddr.sin_addr.s_addr = INADDR_ANY; //0.0.0.0


	InitType type = 0;
	while(tryTimes--)
	{
		this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (serverSocket == -1) {
			type = InitType::SOCKET_ERROR;
			continue ;
		}

		int flags = fcntl(serverSocket, F_GETFL, 0);
		fcntl(this->serverSocket, F_SETFL, flags | O_NONBLOCK);

		if (bind(serverSocket, (struct sockaddr *) &socketAddr, sizeof(socketAddr)) == -1) {
			type = InitType::BIND_ERROR;
			close(serverSocket);
			continue ;
		}

		// Escuchar por conexiones entrantes
		if (listen(serverSocket, 5) == -1) {
			type = InitType::LISTENING_ERROR;
			close(serverSocket);
			continue ;
		}

		return (InitType::SUCCESS);
	}
	return (type);
}


