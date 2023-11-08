/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:23:34 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/20 14:23:34 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"


Server *ServerUtils::getServer(const std::vector<Server *> &servers, const HttpRequest &request) {
	Server *server = 0;

	std::cout << "Request host " << request.getHost() << " - Server socket " << request.getServerSocket() << std::endl;

	for(std::vector<Server *>::const_iterator it = servers.begin(); it != servers.end(); it++) {
		std::cout << "Server server_name " << (*it)->getServerName()  << " - Server socket " << (*it)->getSocket() << std::endl;
		if((*it)->getPort() == request.getPort()) {
			if(!server && (*it)->getServerName() == "" && ((*it)->getHost() == "0.0.0.0" || (*it)->getSocket() == request.getServerSocket()))
				server = *it;
			else if((*it)->getServerName() == request.getHost() && ((*it)->getHost() == "0.0.0.0" || (*it)->getSocket() == request.getServerSocket())) {
				return (Server *) *it;
			}
		}
	}
	return (server);
}
