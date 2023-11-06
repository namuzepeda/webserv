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

#define limitRequestBody	177340032 //7 megabytes
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

struct pollconn {
	long long	lastInteraction;
	bool		differentRead;
};

/******* INIT ERROR HANDLING **********/

enum InitType {
	BIND_ERROR,
	SOCKET_ERROR,
	LISTENING_ERROR,
	SUCCESS
};

enum HttpStatusCode {
	Ok = 200,
	Created = 201,
	MovedPermanently = 301,
	BadRequest = 400,
	Forbidden = 403,
	NotFound = 404,
	MethodNotAllowed = 405,
	RequestTimeout = 408,
	RequestEntityTooLarge = 413,
	RequestUriTooLong = 414,
	InternalServerError = 500,
	VersionNotSupported = 505
};

#include <signal.h>
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
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdexcept>
#include <sys/stat.h>
#include <ctime>
#include <sys/types.h>
#include <dirent.h>

#include "ClientConnection.hpp"
#include "Config.hpp"

#include "StringUtils.hpp"
#include "FileUtils.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpUtils.hpp"
#include "HttpResponseUtils.hpp"
#include "CGIHandler.hpp"

#include "Handler.hpp"
#include "ConfigParser.hpp"
#include "ConfigParserUtils.hpp"


#include "ServerHandler.hpp"
#include "LocationHandler.hpp"

#include "Server.hpp"

#include "StringArrayUtils.hpp"

#include "ServerUtils.hpp"

#include "Core.hpp"


/*************************************/

#endif
