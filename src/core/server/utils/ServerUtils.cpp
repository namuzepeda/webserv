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

Server *server ServerUtils:getServer(std::vector<Server *> &servers, HttpRequest &request) {
	Server *server = 0;
	for(std::vector<Server *>::iterator it = servers.begin(); it != servers.end(); it++) {

	}
}

bool ServerUtils::doesRequestApply(const Server *server, const HttpRequest &request) {
	return (
			(server->getHost() == request.getHost() || server->getHost() == "0.0.0.0") &&
			server->getPort() == request.getPort()
	);

	return (false);
}
