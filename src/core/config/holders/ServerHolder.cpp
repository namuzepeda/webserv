/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHolder.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:28:42 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:16:10 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

ServerHolder::ServerHolder(void): Config() {
	std::cout << "New instance of ServerHolder" << std::endl;
}

ServerHolder::~ServerHolder(void) {

}

bool	ServerHolder::hasServerName(void) {
	return (this->values.find("server_name") != this->values.end());
}

std::string ServerHolder::getServerName() {
	return (this->values["server_name"]);
}

ContextType	ServerHolder::getType(void) {
	return (SERVER);
}
