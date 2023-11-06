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

void LocationHandler::run(HttpRequest &request) {

	std::cout << "Is in lochandler" << std::endl;

	handleHttp(request);
	
	for(std::vector<Handler *>::iterator it = this->childs.begin(); it != this->childs.end(); it++) {
		Handler *handler = *it;
		LocationHandler *locHandler = (LocationHandler *) handler;
		if (request.getLocation().find(locHandler->getPath()) == 0
				|| (locHandler->getPath()[0] == '*' && StringUtils::endsWith(request.getLocation(), locHandler->getPath().substr(1))))
			locHandler->run(request);
	}
}

std::string LocationHandler::getPath() {
	return (this->path);
}
