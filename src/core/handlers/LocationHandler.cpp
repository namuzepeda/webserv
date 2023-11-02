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

	if(this->config->contains("root"))
		request.getConfig()->put("root", this->config->get("root"));
	if(this->config->contains("index"))
		request.getConfig()->put("index", this->config->get("index"));
	if(this->config->contains("autoindex"))
		request.getConfig()->put("autoindex", this->config->get("autoindex"));
	if(this->config->contains("allow_methods"))
		request.getConfig()->put("allow_methods", this->config->get("allow_methods"));
	if(this->config->contains("cgi_pass"))
		request.getConfig()->put("cgi_pass", this->config->get("cgi_pass"));
	if(this->config->contains("error_page")) {
		std::vector<std::string> errorPages = this->config->gets("error_page");
		for(std::vector<std::string>::iterator it = errorPages.begin(); it != errorPages.end(); it++) {
			std::string data = *it;
			std::istringstream iss(data);

			int errorCode;
			std::string errorFile;

			if (iss >> errorCode) {
				std::getline(iss, errorFile);
				errorFile = errorFile.substr(errorFile.find_first_not_of(" "), errorFile.find_last_not_of(" ") + 1);
				std::map<int, std::string>::iterator errorIt = request.getErrorPages().find(errorCode);
				if (errorIt != request.getErrorPages().end()) {
					request.getErrorPages().erase(errorIt);
				}
				request.getErrorPages().insert(std::make_pair(errorCode, errorFile));
			} else
				throw std::runtime_error("Exception trying to extract error number");
		}
	}
	/*for(std::vector<Handler *>::iterator it = this->childs.begin(); it != this->childs.end(); it++) {
		Handler *handler = *it;
		LocationHandler *locHandler = (LocationHandler *) handler;
		std::cout << "Checking route " << request.getLocation() << std::endl;
		if (request.getLocation().find(locHandler->getPath()) == 0) //Handler path found in request path at position 0
			locHandler->run(request);
	}*/
}

std::string LocationHandler::getPath() {
	return (this->path);
}
