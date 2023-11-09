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

Server::Server(ServerHandler *handler): handler(handler), serverName(""), serverSocket(0) {
	this->id = Server::counter++;
	this->host = this->handler->getConfig()->get("host");
	this->port = this->handler->getConfig()->asInt("listen");
	if(this->handler->getConfig()->contains("server_name"))
		this->serverName = this->handler->getConfig()->get("server_name");

	std::string errorFile;

	if (this->handler->getConfig()->contains("error_log")) {
		errorFile = this->handler->getConfig()->get("error_log");
		if(errorFile[0] != '/')
			errorFile = this->handler->getConfig()->get("root") + errorFile;
	}
	else
		errorFile = "/tmp/webserv_" + this->getName();
	this->errorLog = new Logger(errorFile, RED);
	if(this->errorLog->getFd() == -1)
		Logger::info->log(StringUtils::parse("[Server] ID %d - Cannot create log file, please check that folder exists and you have permissions\n", this->id).c_str(), RED);
}

Server::~Server(void) {
	delete this->handler;
	delete this->errorLog;
}

int Server::getPort(void) const {
	return (this->port);
}

std::string	const &Server::getHost(void) const{
	return (this->host);
}

std::string	const &Server::getServerName(void) const{
	return (this->serverName);
}

int	Server::getSocket(void) {
	return (this->serverSocket);
}

std::string Server::getName() {
	std::string name = this->handler->getConfig()->get("host") + "_";
	name += (this->handler->getConfig()->contains("server_name") ? this->handler->getConfig()->get("server_name") : "*");
	name += ".log";
	return (name);
}

InitType Server::init(const std::vector<Server *> &servers, int tryTimes) {

	int use = 1;

	socketAddr.sin_family = AF_INET;
	socketAddr.sin_port = htons(this->port);
	if(!this->host.empty())
		inet_pton(AF_INET, this->host.c_str(), &socketAddr.sin_addr); // //0.0.0.0
	else
		socketAddr.sin_addr.s_addr = INADDR_ANY;
	
	InitType type = BIND_ERROR;
	for(std::vector<Server *>::const_iterator it = servers.begin(); it != servers.end() && (*it)->id != this->id; it++) {
		Server *server = *it;
		if(this->host == server->host && this->port == server->port) {
			this->serverSocket = server->serverSocket;
			return (SUCCESS);
		}
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
		if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &use, sizeof(use)))
		{
			type = BIND_ERROR;
			close(serverSocket);
			continue ;
		}
		if (bind(serverSocket, (struct sockaddr *) &socketAddr, sizeof(socketAddr)) == -1) {
			std::cerr << errno << std::endl;
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
	return (type);
}

ServerHandler *Server::getHandler(void) {
	return (this->handler);
}

Logger	*Server::errors(void) const {
	return (this->errorLog);
}

int		Server::getId() const {
	return (this->id);
}
