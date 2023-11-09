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

void ServerHandler::run(HttpRequest &request) {
	
	if(this->config->contains("root"))
		request.getConfig()->put("froot", this->config->get("root"));
	handleHttp(request);

	for(std::vector<Handler *>::iterator it = this->childs.begin(); it != this->childs.end(); it++) {
		Handler *handler = *it;
		LocationHandler *locHandler = (LocationHandler *) handler;

 		if (request.getLocation().substr(0, locHandler->getPath().length()) == locHandler->getPath()
				|| (locHandler->getPath()[0] == '*' && StringUtils::endsWith(request.getLocation(), locHandler->getPath().substr(1))) ) {
			locHandler->run(request);
		}
	}
}
