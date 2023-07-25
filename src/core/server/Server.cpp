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

Server::Server(const ServerHandler &handler) {
	this->handler = handler;





}

bool Server::init() {
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		std::cerr << "Error al crear el socket." << std::endl;
		return 1;
	}

	// Configurar el socket del servidor como no bloqueante
	int flags = fcntl(serverSocket, F_GETFL, 0);
	fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);

	// Configurar la dirección del servidor
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(8080); // Puerto 8080 para escuchar

	// Enlazar el socket al puerto y la dirección
	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		std::cerr << "Error en el enlace del socket." << std::endl;
		close(serverSocket);
		return 1;
	}

	// Escuchar por conexiones entrantes
	if (listen(serverSocket, 5) == -1) {
		std::cerr << "Error al intentar escuchar." << std::endl;
		close(serverSocket);
		return 1;
	}

	std::cout << "Servidor HTTP iniciado. Esperando conexiones..." << std::endl;
}


