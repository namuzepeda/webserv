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

#include "Handler.hpp"

Handler::Handler(Config *config) {
	this->config = config;
}

Config *Handler::getConfig(void) {
	return (this->config);
}

std::set<Handler *> const	&Handler::getChilds() const {
	return (this->childs);
}
