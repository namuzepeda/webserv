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

#pragma once

#include <iostream>
#include <string>

enum ContextType {
	SERVER,
	LOCATION
};

enum RequestType {
	GET,
	POST,
	DELETE
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

    Token(TokenType type, std::string value) : type(type), value(value) {}
};

/******* INIT ERROR HANDLING **********/

enum InitType {
	BIND_ERROR,
	SOCKET_ERROR,
	LISTENING_ERROR,
	SUCCESS
};


#include <algorithm>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

#include "Config.hpp"
#include "Handler.hpp"
#include "ConfigParser.hpp"
#include "ConfigParserUtils.hpp"

#include "ServerHolder.hpp"
#include "LocationHolder.hpp"


#include "ServerHandler.hpp"
#include "LocationHandler.hpp"

#include "Server.hpp"

#include "StringArrayUtils.hpp"

#include "URI.hpp"

#include "ServerUtils.hpp"

#include "Core.hpp"


/*************************************/

#endif
