/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:01:59 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 21:01:59 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Config.hpp"

Config::Config(void) {
	this->childs = 0;
	this->parent = 0;
}

Config::hasChilds(void) {
	return false;
}

Config::getChilds(void) {
	return this->childs;
}
