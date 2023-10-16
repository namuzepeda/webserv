/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/10/16 18:57:40 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "WebServ.hpp"

class HttpRequest
{
	private:

		std::string							line;
		std::string							type;
		std::string							location;
		std::string							version;
		std::string							parameters;
		std::map<std::string, std::string>	headers;
		std::string							host;
		std::string							port;
		std::string							body;
		Config								config;

	public:

		HttpRequest(const char * buffer);
		~HttpRequest();

		std::string	const &getReqLine() const;
		std::string	const &getType() const;
		std::string	const &getLocation() const;
		std::string	const &getParameters() const;
		std::string	const &getVersion() const;
		std::string	const &getBody() const;
		std::map<std::string, std::string> const &getHeaders() const;
		bool		headContains(const std::string& key);
		std::string	getHeadValue(const std::string& key);
		std::string	const &getHost() const;
		std::string const &getPort() const;		
		Config		const &getConfig() const;				

};

std::ostream &operator<<(std::ostream &o, HttpRequest const &i);

#endif
