/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:26:01 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:06:35 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

LocationHandler::LocationHandler(Config *config, std::string path): Handler(config), path(path) {

}

LocationHandler::~LocationHandler() {

}

void LocationHandler::run(const HttpRequest &request) {
	/*if(this->getConfig("cgi_pass") != NULL)
	{
		request->getConfig().put("cgi_pass", this->getConfig("cgi_pass"));
	}
	if(this->getConfig("root") != NULL)
	{
		request->getConfig().put("root", this->getConfig("root"));
	}*/
	for(std::vector<Handler *>::iterator it = this->childs.begin(); it != this->childs.end(); it++) {
		Handler *handler = *it;
		if(handler->getConfig()->getType() == LOCATION) {
			LocationHandler *locHandler = (LocationHandler *) handler;
			if (request.getLocation().find(locHandler->getPath()) == 0) //Handler path found in request path at position 0
				locHandler->run(request);
		}
	}
}

std::string LocationHandler::getPath() {
	return (this->path);
}
