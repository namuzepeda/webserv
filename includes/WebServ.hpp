/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:35:06 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/20 17:35:06 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_H
#define WEBSERV_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

enum ContextType {
	SERVER
};

enum RequestType {
	GET,
	POST,
	DELETE
};

std::string IDENTIFIERS[] = {
		"listen",
		"server_name",
		"host",
		"root",
		"error_page",
		"location",
		"allow_methods",
		"autoindex",
		"index",
		"return",
		"cgi_path",
		"cgi_ext"
};

enum TokenType {
    Identifier,
    Value,
    BlockStart,
    BlockEnd,
    Semicolon,
    Invalid
};

struct Token {
    TokenType type;
    std::string value;
};

/******* INIT ERROR HANDLING **********/

enum InitType {
	BIND_ERROR,
	SOCKET_ERROR,
	LISTENING_ERROR,
	SUCCESS
};

/*************************************/

#endif
