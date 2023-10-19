/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:35:06 by nmunoz            #+#    #+#             */
/*   Updated: 2023/10/18 23:48:43 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_H
#define WEBSERV_H

#pragma once

#include <iostream>
#include <string>

#define limitRequestBody	7340032 //7 megabytes
#define limitUriSize		4096 //characters
#define limitHeaderSize		5000 // 5 kilobytes
//longitud maxima de encabezados en bytes
//longitud maxima de campos en formularios en caracteres
//tamano maximo de carga util megabites
//tamano maximo dearchivos que puedan descargarse megabtes

enum ContextType {
	SERVER,
	LOCATION
};

enum RequestType {
	GET,
	POST,
	DELETE,
	NONE
};

enum TokenType {
    IDENTIFIER,
    VALUE,
    BLOCK_START,
    BLOCK_END,
    SEMICOLON,
	CONTEXT,
    INVALID
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

enum HttpStatusCode {
	OK = 200,
	Created = 201,
	BadRequest = 400,
	NotFound = 404,
	MethodNotAllowed = 405,
	RequestEntityTooLarge = 413,
	RequestUriTooLong = 414,
	VersionNotSupported = 505,
	InternalServerError = 500
};

#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpResponseUtils.hpp"
#include "CGIHandler.hpp"

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

#include "ServerUtils.hpp"

#include "Core.hpp"


/*************************************/

#endif
