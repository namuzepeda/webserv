/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:26:01 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:06:35 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

ServerHandler::ServerHandler(Config *config): Handler(config) {

}

ServerHandler::~ServerHandler() {

}

void ServerHandler::run(const HttpRequest &request, const HttpResponse &response) {
	for(std::vector<Handler *>::iterator it = this->childs.begin(); it != this->childs.end(); it++) {
		Handler *handler = *it;
		if(handler->getConfig()->getType() == LOCATION) {
			LocationHandler *locHandler = (LocationHandler *) handler;
			if (request.getLocation().find(locHandler->getPath()) != 0) //Handler path found in request path at position 0
				return ;
			locHandler->run(request, response);
		}
		handler->run(request, response);
	}
}
