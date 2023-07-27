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

/*static bool containsPort(Server &server, int port) {
	std::vector<int> ports = server.getPorts();
	for (std::vector<int>::iterator it = ports.begin(); it != ports.end(); ++it) {
		if (*it == port)
			return (true);
	}
	return (false);
}*/

bool ServerUtils::doesRequestApply(Server &server, HttpRequest &request) {
	(void) server;
	(void) request;
	/*URI uri = request.getURI();

	return (
			server.getHost().compare(uri.getHost()) == 0 &&
			containsPort(server, uri.getPort())
	);*/
	return false;
}
