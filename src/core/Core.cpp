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
				std::cerr << "SUCCESS" << std::endl;
			} else {
				delete server;
				std::cerr << "ERROR " << initType << std::endl;
			}
		}
		handlers.clear();
		run();
	} catch (const std::runtime_error &error) {
		std::cerr << "Error: " << error.what() << std::endl;
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
}

std::string Core::getResponse(HttpRequest &request) {

	for(std::vector<Server *>::iterator it = this->servers.begin(); it != this->servers.end(); it++) {
		Server *server = *it;
		if(ServerUtils::doesRequestApply(*server, request)) {
			server->getHandler()->run(request);

			

			HttpResponse response(request);
			//std::cout << response.toString() << std::endl;
			return (response.toString(request));
		}
	}
	//response = HttpRequest();
	//response.statusCode = 400; //Bad request
	//return (response.toString());
	return (HttpResponseUtils::testResponse(InternalServerError, HttpResponseUtils::errorBody(InternalServerError)));
}

void	Core::run(void) {

	std::vector<int> sockets;
	std::vector<pollfd> pollEvents;

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
						std::cerr << "Error al aceptar la conexión." << std::endl;
					} else {
						std::cout << "Conexión establecida con un cliente." << std::endl;
						int flags = fcntl(clientSocket, F_GETFL, 0);
						fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
						clientSockets.push_back(clientSocket);
					}
				}
			}
			for (size_t i = sockets.size(); i < pollEvents.size(); ++i) {
				if ((pollEvents[i].revents & POLLIN) || (pollEvents[i].revents & POLLOUT)) {
					char buffer[Config::DEFAULT_BUFFER_SIZE] = {0};
					int bytesRead = recv(pollEvents[i].fd, buffer, sizeof(buffer) + 1, 0);
					if (bytesRead <= 0) {
						clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), pollEvents[i].fd), clientSockets.end());
						close(pollEvents[i].fd);
						std::cout << "Conexión cerrada con un cliente." << std::endl;
					} else {
						buffer[bytesRead] = '\0';
						ClientConnection::requests[pollEvents[i].fd] += buffer;
						if(ClientConnection::isRequestCompleted(pollEvents[i].fd)) {
							std::cout << "Request completed" << std::endl;
							HttpRequest request(ClientConnection::getBuffer(pollEvents[i].fd).c_str());
							std::string response = getResponse(request);
							send(pollEvents[i].fd, response.c_str(), response.length(), 0);
							close(pollEvents[i].fd);
							//if(!request.headContains("Keep-alive")) {
							//	clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), pollEvents[i].fd), clientSockets.end());
							//	close(pollEvents[i].fd);
							//}
						} else {
							std::cout << "Request NOT completed" << std::endl;
						}
					}
				}
			}
		} else {
			if(!Core::stopped)
				std::cerr << "Error en la función poll()." << std::endl;
		}
	}

	// Cerrar los sockets de los clientes que aún estén abiertos
	for (size_t i = 0; i < clientSockets.size(); ++i) {
		std::cout << "Closing client socket !" << std::endl;
		close(clientSockets[i]);
	}

	// Cerrar los sockets del servidor
	for (std::vector<int>::iterator it = sockets.begin(); it != sockets.end(); it++) {
		int serverSocket = *it;
		std::cout << "Closing server socket !" << std::endl;
		close(serverSocket);
	}
}

std::vector<Server *> const &Core::getServers(void) const {
	return (this->servers);
}

