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

	for(std::vector<Server *>::const_iterator it = servers.begin(); it != servers.end(); it++) {
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
