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

void ServerHandler::run(const HttpRequest &request) {
	Config *rConfig = request.getConfig();
	rConfig->put("root", this->config->get("root"));
	if(this->config->contains("index"))
		rConfig->put("index", this->config->get("index"));
	if(this->config->contains("autoindex"))
		rConfig->put("autoindex", this->config->get("autoindex"));
	if(this->config->contains("allow_methods"))
		rConfig->put("allow_methods", this->config->get("allow_methods"));
	for(std::vector<Handler *>::iterator it = this->childs.begin(); it != this->childs.end(); it++) {
		Handler *handler = *it;
		LocationHandler *locHandler = (LocationHandler *) handler;

 		if (request.getLocation().substr(0, locHandler->getPath().length()) == locHandler->getPath()) {
			locHandler->run(request);
		}
	}
}
