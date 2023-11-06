/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:32:46 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 22:32:46 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

Handler::Handler(Config *config): config(config) {

}

Handler::~Handler() {
	for(std::vector<Handler *>::iterator it = this->childs.begin(); it != this->childs.end(); it++) {
		Handler *handler = *it;
		delete handler;
	}
	this->childs.clear();
	delete this->config;
}

void	Handler::handleHttp(HttpRequest &request) {
	int idSize = StringArrayUtils::size(ConfigParserUtils::IDENTIFIERS);
	for(int i = 0; idSize > i; i++) {
		std::string id = ConfigParserUtils::IDENTIFIERS[i];
		if(this->config->contains(id)) {
			if(id == "error_page") {
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
			} else {
				//std::cout << "Setting " << id << " = " << this->config->get(id) << std::endl;
				request.getConfig()->put(id, this->config->get(id));
			}
		}
			
	}
}

Config *Handler::getConfig(void) {
	return (this->config);
}

void Handler::setConfig(Config *config) {
	this->config = config;
}

std::vector<Handler *> const	&Handler::getChilds(void) const {
	return (this->childs);
}

void	Handler::addChild(Handler *handler) {
	this->childs.push_back(handler);
}

bool	Handler::hasChilds(void) {
	return (this->childs.size() > 0);
}







