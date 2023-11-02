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

std::string Config::get(const std::string &key) {
	std::map<std::string, std::vector<std::string> >::iterator it = this->values.find(key);
	if(it != this->values.end())
		return (it->second[it->second.size() - 1]);
	return (0);
}

std::vector<std::string> Config::gets(const std::string &key) {
	std::map<std::string, std::vector<std::string> >::iterator it = this->values.find(key);
	if(it != this->values.end())
		return (it->second);
	std::vector<std::string> data;
	this->values.insert(std::make_pair(key, data));
	return (Config::gets(key));
}

bool Config::contains(const std::string &key) {
	std::map<std::string, std::vector<std::string> >::const_iterator it = this->values.find(key);

	if (it == this->values.end()) {
		return false;
	}
	return (it->second.size());
}

void Config::remove(const std::string &key) {
	std::map<std::string, std::vector<std::string> >::iterator it = this->values.find(key);
    if (it != this->values.end()) {
        this->values.erase(it);
    }
}

void Config::put(std::string key, std::string value) {
	if(contains(key)) {
		remove(key);
	}
	std::vector<std::string> data;
	data.push_back(value);
	this->values.insert(std::make_pair(key, data));
}

void Config::add(std::string key, std::string value) {
	if(!contains(key))
		Config::put(key, value);
	else
		gets(key).push_back(value);
}