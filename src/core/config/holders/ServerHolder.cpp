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

#include "../../../../../includes/ServerHolder.hpp"

ServerHolder::ServerHolder() {
	std::cout << "New instance of ServerHolder" << std::endl;
}

ServerHolder::getServerName() {
	std::string value = this->map->find("server_name");
	return value->first;
}

ServerHolder::getType() {
	return SERVER;
}