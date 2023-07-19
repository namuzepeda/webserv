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

#include "../../../includes/Handler.hpp"

Handler::Handler(const Config &config) {
	this->childs = 0;
	this->config = 0;
}

Config const &Handler::getConfig(void) const {
	return (this->config);
}

std::set<Handler*> const	&Handler::getChilds() const {
	return (this->childs);
}
