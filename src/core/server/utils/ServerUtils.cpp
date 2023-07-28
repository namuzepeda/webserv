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

bool ServerUtils::containsPort(const Server &server, int port) {
	const std::vector<int> ports = server.getPorts();
	for (std::vector<int>::const_iterator it = ports.begin(); it != ports.end(); ++it) {
		if (*it == port)
			return (true);
	}
	return (false);
}

bool ServerUtils::doesRequestApply(const Server &server, const HttpRequest &request) {
	URI uri = request.getURI();

	return (
			server.getHost() == uri.getHost() &&
			containsPort(server, uri.getPort())
	);
	return false;
}
