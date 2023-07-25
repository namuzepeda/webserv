/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:42:16 by gamoreno          #+#    #+#             */
/*   Updated: 2023/07/25 16:24:28 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <iostream>
// #include <cstring>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <fcntl.h> // Para configurar sockets no bloqueantes
// #include <vector>
// #include <poll.h>

// std::string processRequest(const std::string& requestMethod) {
//     if (requestMethod == "GET") {
//         return "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hola desde el servidor (Método GET)</h1></body></html>";
//     } else if (requestMethod == "POST") {
//         return "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hola desde el servidor (Método POST)</h1></body></html>";
//     } else if (requestMethod == "DELETE") {
//         return "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hola desde el servidor (Método DELETE)</h1></body></html>";
//     } else {
//         return "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Error: Método no soportado</h1></body></html>";
//     }
// }

// int main() {
//     // Crear el socket del servidor
//     int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//     if (serverSocket == -1) {
//         std::cerr << "Error al crear el socket." << std::endl;
//         return 1;
//     }

//     // Configurar el socket del servidor como no bloqueante
//     int flags = fcntl(serverSocket, F_GETFL, 0);
//     fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);

//     // Configurar la dirección del servidor
//     sockaddr_in serverAddr;
//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_addr.s_addr = INADDR_ANY;
//     serverAddr.sin_port = htons(8080); // Puerto 8080 para escuchar

//     // Enlazar el socket al puerto y la dirección
//     if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
//         std::cerr << "Error en el enlace del socket." << std::endl;
//         close(serverSocket);
//         return 1;
//     }

//     // Escuchar por conexiones entrantes
//     if (listen(serverSocket, 5) == -1) {
//         std::cerr << "Error al intentar escuchar." << std::endl;
//         close(serverSocket);
//         return 1;
//     }

//     std::cout << "Servidor HTTP iniciado. Esperando conexiones..." << std::endl;

//     // Vector para almacenar los sockets de los clientes conectados
//     std::vector<int> clientSockets;
//     std::vector<pollfd> pollEvents;

//     while (true) {
//         // Crear estructura de eventos para poll
//         pollEvents.clear(); // Limpiar el vector en cada iteración

//         // Agregar el socket del servidor a los eventos a monitorear
//         pollfd serverEvent;
//         serverEvent.fd = serverSocket;
//         serverEvent.events = POLLIN; // Esperar eventos de lectura (nuevas conexiones)
//         pollEvents.push_back(serverEvent);

//         // Agregar los sockets de los clientes a los eventos a monitorear
//         for (size_t i = 0; i < clientSockets.size(); ++i) {
//             pollfd clientEvent;
//             clientEvent.fd = clientSockets[i];
//             clientEvent.events = POLLIN | POLLOUT; // Esperar eventos de lectura y escritura
//             pollEvents.push_back(clientEvent);
//         }

//         // Esperar eventos en los sockets con un tiempo de espera infinito (-1)
//         int ready = poll(&pollEvents[0], pollEvents.size(), -1);
//         if (ready == -1) {
//             std::cerr << "Error en la función poll()." << std::endl;
//             break;
//         }

//         // Comprobar eventos en el socket del servidor
//         if (pollEvents[0].revents & POLLIN) {
//             // Aceptar una nueva conexión entrante
//             sockaddr_in clientAddr;
//             socklen_t clientAddrSize = sizeof(clientAddr);
//             int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
//             if (clientSocket == -1) {
//                 std::cerr << "Error al aceptar la conexión." << std::endl;
//             } else {
//                 std::cout << "Conexión establecida con un cliente." << std::endl;

//                 // Configurar el socket del cliente como no bloqueante
//                 int flags = fcntl(clientSocket, F_GETFL, 0);
//                 fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);

//                 // Agregar el nuevo socket del cliente al vector de clientes
//                 clientSockets.push_back(clientSocket);
//             }
//         }

//         // Comprobar eventos en los sockets de los clientes
//         for (size_t i = 1; i < pollEvents.size(); ++i) {
//             if (pollEvents[i].revents & POLLIN || pollEvents[i].revents & POLLOUT) {
//                 char buffer[1024] = {0};
//                 int bytesRead = recv(pollEvents[i].fd, buffer, sizeof(buffer) - 1, 0);
//                 if (bytesRead <= 0) {
//                     // El cliente ha cerrado la conexión o ha ocurrido un error
//                     close(pollEvents[i].fd);
//                     std::cout << "Conexión cerrada con un cliente." << std::endl;

//                     // Eliminar el socket del cliente del vector de clientes
//                     clientSockets.erase(clientSockets.begin() + i - 1);
//                 } else {
//                     // Procesar la solicitud del cliente
//                     buffer[bytesRead] = '\0'; // Asegurarnos de terminar el buffer como una cadena de caracteres

//                     // Extraer el método de la solicitud del buffer directamente
//                     std::string requestMethod = buffer;
//                     std::string::size_type pos = requestMethod.find(' ');
//                     if (pos != std::string::npos) {
//                         requestMethod = requestMethod.substr(0, pos);
//                     }

//                     // Obtener la respuesta basada en el método de la solicitud
//                     std::string httpResponse = processRequest(requestMethod);

//                     // Enviar la respuesta al cliente
//                     send(pollEvents[i].fd, httpResponse.c_str(), httpResponse.length(), 0);
//                 }
//             }
//         }
//     }

//     // Cerrar los sockets de los clientes que aún estén abiertos
//     for (size_t i = 0; i < clientSockets.size(); ++i) {
//         close(clientSockets[i]);
//     }

//     // Cerrar el socket del servidor
//     close(serverSocket);

//     return 0;
// }

#include "../includes/WebServ.hpp"
#include "../includes/Core.hpp"


int main(void)
{
    
    return 0;
}
