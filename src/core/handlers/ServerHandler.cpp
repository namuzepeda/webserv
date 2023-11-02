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

bool endsWith(const std::string& fullString, const std::string& ending) {
    if (fullString.length() >= ending.length()) {
        return fullString.compare(fullString.length() - ending.length(), ending.length(), ending) == 0;
    } else {
        return false;
    }
}

void ServerHandler::run(HttpRequest &request) {
	Config *rConfig = request.getConfig();
	rConfig->put("root", this->config->get("root"));
	rConfig->put("froot", this->config->get("root"));
	if(this->config->contains("index"))
		rConfig->put("index", this->config->get("index"));
	if(this->config->contains("autoindex"))
		rConfig->put("autoindex", this->config->get("autoindex"));
	if(this->config->contains("allow_methods"))
		rConfig->put("allow_methods", this->config->get("allow_methods"));
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
	for(std::vector<Handler *>::iterator it = this->childs.begin(); it != this->childs.end(); it++) {
		Handler *handler = *it;
		LocationHandler *locHandler = (LocationHandler *) handler;

 		if (request.getLocation().substr(0, locHandler->getPath().length()) == locHandler->getPath()
				|| (locHandler->getPath()[0] == '*' && endsWith(request.getLocation(), locHandler->getPath().substr(1))) ) {
			locHandler->run(request);
		}
	}
}
