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

bool ServerUtils::doesRequestApply(const Server &server, const HttpRequest &request) {
	/*return (
			server.getHost() == request.getHost() &&
			server.getPort() == request.getPort()
	);*/
	(void) server;
	(void) request;
	return false;
}
