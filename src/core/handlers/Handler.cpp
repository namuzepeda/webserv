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

}

Config *Handler::getConfig(void) {
	return (this->config);
}

std::set<Handler *> const	&Handler::getChilds(void) const {
	return (this->childs);
}

bool	Handler::hasChilds(void) {
	return (this->childs.size() > 0);
}







