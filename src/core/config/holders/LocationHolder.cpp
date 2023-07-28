/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationHolder.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:28:42 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:16:10 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

LocationHolder::LocationHolder(void): Config() {
	std::cout << "New instance of LocationHolder" << std::endl;
}

LocationHolder::~LocationHolder(void) {

}

ContextType	LocationHolder::getType(void) {
	return (SERVER);
}
