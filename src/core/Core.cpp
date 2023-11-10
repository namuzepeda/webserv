#include "WebServ.hpp"

/************** STATIC ******************/

/*void			Core::deleteInstance(void)	{
	delete instance;
	instance = 0;
}*/

/****************************************/



Core::Core(const std::ifstream &configFile) {
	std::vector<Token *> tokens = ConfigParser::parse(configFile);
	try {
		std::vector<Handler *> handlers = ConfigParser::getHandlers(tokens);
		for(std::vector<Handler *>::iterator it = handlers.begin(); it != handlers.end(); it++) {
			Server *server = new Server((ServerHandler *) *it);
			InitType initType = server->init(this->servers, 3);
			if(initType == SUCCESS) {
				this->servers.push_back(server);
				Logger::info->log(StringUtils::parse("[Server] ID %d - Correctly opened\n", server->getId()).c_str());
			} else {
				delete server;
				Logger::info->log(StringUtils::parse("[Server] ID %d - Error at opening\n", server->getId()).c_str(), RED);
			}
		}
		handlers.clear();
		run();
	} catch (const std::runtime_error &error) {
		Logger::info->log(StringUtils::parse("[WebServ][Fatal] ERROR - %s\n", error.what()).c_str(), RED);
	}
	for(std::vector<Token *>::iterator it = tokens.begin(); it != tokens.end(); it++) {
		Token *token = *it;
		delete token;
	}
	tokens.clear();
}

Core::~Core() {
	for (std::vector<Server *>::iterator it = this->servers.begin(); it != this->servers.end(); ++it) {
		Server *server = *it;
		delete server;
	}
	this->servers.clear();
	delete Logger::info;
}

void  handleRequest(HttpRequest &request, Server *server) {
	server->getHandler()->run(request);

	if(request.getLocation()[request.getLocation().length() - 1] == '/' 
		&& (!request.getConfig()->contains("autoindex") || request.getConfig()->get("autoindex") != "on")) {
		
		std::string location = request.getLocation();
		location += HttpResponseUtils::getIndex(request);
		request.setLocation(location);
		handleRequest(request, server);
	} else
		if(request.getLocation()[0] == '/')
			request.setLocation(request.getLocation().substr(1));
}

std::string Core::getResponse(int socket) {
	std::string buffer = ClientConnection::getBuffer(socket);
	HttpRequest request(buffer, ClientConnection::clientServer[socket]);

	Server *server = ServerUtils::getServer(this->servers, request);
	if(!server)
		return "";
	handleRequest(request, server);

	Logger::info->log(StringUtils::parse("[Server] ID %d - \033[33mIncoming request: Location %s \033[92m- \033[33mReturning file/directory: %s\n", ClientConnection::clientServer[socket], request.getLocation().c_str(), request.getFullPath().c_str()).c_str());

	HttpResponse response(request, request.getConfig()->contains("cgi_pass"), server);

	return (response.toString(request));
}

void	Core::run(void) {

	std::vector<int> sockets;
	std::vector<pollfd> pollEvents;
	std::map<int, pollconn> pollConnections;

	for(std::vector<Server *>::iterator it = this->servers.begin(); it != this->servers.end(); it++)
	{
		std::vector<int>::iterator findIt = std::find(sockets.begin(), sockets.end(), (*it)->getSocket());
		if(findIt == sockets.end()) { //No contiene socket
			sockets.push_back((*it)->getSocket());
			pollfd serverEvent;
			serverEvent.fd = (*it)->getSocket();
			serverEvent.events = POLLIN;
			pollEvents.push_back(serverEvent);
		}
	}

	std::vector<int> clientSockets;

	while (!Core::stopped) {
		pollEvents.erase(pollEvents.begin() + sockets.size(), pollEvents.end());
		for (size_t i = 0; i < clientSockets.size(); ++i) {
			pollfd clientEvent;
			clientEvent.fd = clientSockets[i];
			clientEvent.events = POLLIN | POLLOUT;
			pollEvents.push_back(clientEvent);
		}
		int ready = poll(&pollEvents[0], pollEvents.size(), -1);
		if (ready != -1) {
			for (size_t i = 0; i < sockets.size(); ++i) {
				if (pollEvents[i].revents & POLLIN) {
					sockaddr_in clientAddr;
					socklen_t clientAddrSize = sizeof(clientAddr);
					int clientSocket = accept(sockets[i], (struct sockaddr*)&clientAddr, &clientAddrSize);
					if (clientSocket == -1) {
						Logger::info->log(StringUtils::parse("[Server] ID %d - Error accepting client connection\n", sockets[i]).c_str(), RED);
					} else {
						ClientConnection::clientServer[clientSocket] = sockets[i];
						Logger::info->log(StringUtils::parse("[Server] ID %d - Connection established with client\n", sockets[i]).c_str());
						int flags = fcntl(clientSocket, F_GETFL, 0);
						fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
						clientSockets.push_back(clientSocket);
						pollConnections[clientSocket].lastInteraction = 0;
					}
				}
			}
			for (size_t i = sockets.size(); i < pollEvents.size(); ++i) {
				if ((pollEvents[i].revents & POLLIN)) {
					char buffer[32768] = {0};
					int bytesRead = recv(pollEvents[i].fd, buffer, 32768, 0);
					struct timeval currentTime;
					gettimeofday(&currentTime, NULL);
					long long time = currentTime.tv_sec * 1000LL + currentTime.tv_usec;
					pollConnections[pollEvents[i].fd].lastInteraction = time;
					pollConnections[pollEvents[i].fd].differentRead = bytesRead != 32768;
					if (bytesRead == -1 || bytesRead == 0) {
						clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), pollEvents[i].fd), clientSockets.end());
						close(pollEvents[i].fd);
						ClientConnection::deleteBuffer(pollEvents[i].fd);
						Logger::info->log(StringUtils::parse("[Server] ID %d - Client connection closed\n", ClientConnection::clientServer[pollEvents[i].fd]).c_str(), YELLOW);
					} else {
						std::string sBuffer(buffer, bytesRead);
						ClientConnection::requests[pollEvents[i].fd] += sBuffer;
					}
				} else if(pollEvents[i].revents & POLLOUT) {
					std::map<int, pollconn>::iterator it = pollConnections.find(pollEvents[i].fd);
					if(it != pollConnections.end()) {
						struct timeval currentTime;
						gettimeofday(&currentTime, NULL);
						long long time = currentTime.tv_sec * 1000LL + currentTime.tv_usec;
						if((pollConnections[pollEvents[i].fd].differentRead || (pollConnections[pollEvents[i].fd].lastInteraction != 0 && time - pollConnections[pollEvents[i].fd].lastInteraction >= 50)) && ClientConnection::isRequestCompleted(pollEvents[i].fd)) {
							std::string response = getResponse(pollEvents[i].fd);
							if(!response.empty() && send(pollEvents[i].fd, response.c_str(), response.length(), 0) <= 0) {
								Logger::info->log(StringUtils::parse("[Server] ID %d - Error sending response to client\n", ClientConnection::clientServer[pollEvents[i].fd]).c_str(), RED);
							}
							ClientConnection::deleteBuffer(pollEvents[i].fd);
							close(pollEvents[i].fd);
							Logger::info->log(StringUtils::parse("[Server] ID %d - Client connection closed\n", ClientConnection::clientServer[pollEvents[i].fd]).c_str(), YELLOW);
							clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), pollEvents[i].fd), clientSockets.end());
							pollConnections.erase(it);
							continue ;
						}
					}
				}
				struct timeval currentTime;
				gettimeofday(&currentTime, NULL);
				long long time = currentTime.tv_sec * 1000LL + currentTime.tv_usec;
				long long rest = abs(time - pollConnections[pollEvents[i].fd].lastInteraction);
				if(pollConnections[pollEvents[i].fd].lastInteraction != 0 && rest >= timeOut) {
					std::string response = HttpResponseUtils::testResponse(GatewayTimeout, HttpResponseUtils::errorBody(GatewayTimeout));
					if(send(pollEvents[i].fd, response.c_str(), response.length(), 0) <= 0) {
						Logger::info->log(StringUtils::parse("[Server] ID %d - Error sending response to client\n", ClientConnection::clientServer[pollEvents[i].fd]).c_str(), RED);
					}
					ClientConnection::deleteBuffer(pollEvents[i].fd);
					close(pollEvents[i].fd);
					Logger::info->log(StringUtils::parse("[Server] ID %d - Client connection closed\n", ClientConnection::clientServer[pollEvents[i].fd]).c_str(), YELLOW);
					clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), pollEvents[i].fd), clientSockets.end());
					pollConnections.erase(pollConnections.find(pollEvents[i].fd));
				}
				
			}
		} else {
			if(!Core::stopped)
				Logger::info->log(StringUtils::parse("[WebServ][Fatal] Error with poll function\n").c_str(), YELLOW);
		}
	}

	// Cerrar los sockets de los clientes que aún estén abiertos
	for (size_t i = 0; i < clientSockets.size(); ++i) {
		close(clientSockets[i]);
	}

	// Cerrar los sockets del servidor
	int i = 0;
	for (std::vector<int>::iterator it = sockets.begin(); it != sockets.end(); it++) {
		int serverSocket = *it;
		Logger::info->log(StringUtils::parse("[Server] ID %d - Closing server socket\n", i++).c_str(), YELLOW);
		close(serverSocket);
	}
}

std::vector<Server *> const &Core::getServers(void) const {
	return (this->servers);
}

