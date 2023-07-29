#include "WebServ.hpp"

Core	*Core::getInstance(void)	{
	return instance;
}

/************** STATIC ******************/



/*void			Core::deleteInstance(void)	{
	delete instance;
	instance = 0;
}*/

/****************************************/



Core::Core(const std::ifstream &configFile) {
	instance = this;
	try {
		std::vector<Handler *> handlers = ConfigParser::getHandlers(configFile);
		for(std::vector<Handler *>::iterator it = handlers.begin(); it != handlers.end(); it++) {
			Server server = Server((ServerHandler *) *it);
			InitType initType = server.init(3);
			if(initType == SUCCESS)
				this->servers.push_back(server);
			else {
				//Error
			}
		}
	} catch (const std::runtime_error& error) {
		std::cerr << error.what() << std::endl;
	}
}

HttpResponse *Core::getResponse(const HttpRequest &request) {
	HttpResponse *response = new HttpResponse();
	for(std::vector<Server>::iterator it = this->servers.begin(); it != this->servers.end(); it++) {
		Server server = *it;
		if(ServerUtils::doesRequestApply(server, request)) {
			server.getHandler()->run(request, *response);
		}
		return (response);
	}
	return (NULL);
}

void	Core::run(void) {

	std::vector<int> sockets;

	for(std::vector<Server>::iterator it = this->servers.begin(); it != this->servers.end(); it++)
	{
		std::vector<int>::iterator findIt = std::find(sockets.begin(), sockets.end(), (*it).getSocket());
		if(findIt == sockets.end()) { //No contiene socket
			sockets.push_back((*it).getSocket());
		}
	}

	std::vector<int> clientSockets;
	std::vector<pollfd> pollEvents;

	while (true) {
		pollEvents.clear();

		for (std::vector<int>::iterator it = sockets.begin(); it != sockets.end(); it++) {
			int serverSocket = *it;
			pollfd serverEvent;
			serverEvent.fd = serverSocket;
			serverEvent.events = POLLIN;
			pollEvents.push_back(serverEvent);
		}

		for (size_t i = 0; i < clientSockets.size(); ++i) {
			pollfd clientEvent;
			clientEvent.fd = clientSockets[i];
			clientEvent.events = POLLIN | POLLOUT;
			pollEvents.push_back(clientEvent);
		}

		int ready = poll(&pollEvents[0], pollEvents.size(), -1);
		if (ready == -1) {
			std::cerr << "Error en la función poll()." << std::endl;
			break;
		}

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
			if (pollEvents[i].revents & POLLIN || pollEvents[i].revents & POLLOUT) {
				char buffer[Config::DEFAULT_BUFFER_SIZE] = {0};
				int bytesRead = recv(pollEvents[i].fd, buffer, sizeof(buffer) + 1, 0);

				if (bytesRead <= 0) {
					// El cliente ha cerrado la conexión o ha ocurrido un error
					 close(pollEvents[i].fd);
					 std::cout << "Conexión cerrada con un cliente." << std::endl;

					 // Eliminar el socket del cliente del vector de clientes
					 clientSockets.erase(clientSockets.begin() + i);
				} else {
					 // Procesar la solicitud del cliente
					 buffer[bytesRead] = '\0'; // Asegurarnos de terminar el buffer como una cadena de caracteres
					 HttpRequest *request = HttpRequest::build(buffer);
					 HttpResponse *response = getResponse(*request);
					 if(response) {
						 std::string responseString = response->toString();
						 send(pollEvents[i].fd, responseString.c_str(), responseString.length(), 0);
					 }
					 //if(!request->getHeaders()->contains("Keep-alive")) {
					//	 clientSockets.erase(clientSockets.begin() + i);
					 //}
				}
			}
		}
	}

	// Cerrar los sockets de los clientes que aún estén abiertos
	for (size_t i = 0; i < clientSockets.size(); ++i) {
		close(clientSockets[i]);
	}

	// Cerrar los sockets del servidor
	for (std::vector<int>::iterator it = sockets.begin(); it != sockets.end(); it++) {
		int serverSocket = *it;
		close(serverSocket);
	}
}

Core::~Core() {

}


std::vector<Server> const &Core::getServers(void) const {
	return (this->servers);
}

