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







