/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:01:59 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/25 16:46:36 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

Config::Config(void) {

}

Config::~Config(void) {

}

int	Config::asInt(std::string key) {
	return atoi(this->get(key).c_str());
}

std::string Config::get(std::string key) {
	std::map<std::string, std::string>::iterator it = this->values.find(key);
	if(it != this->values.end())
		return (it->second);
	return (0);
}
