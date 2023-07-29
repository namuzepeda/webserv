/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 21:03:32 by nmunoz           ###   ########.fr       */
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
		std::map<std::string, std::string>	headers;
		std::string							body;

	public:

		HttpRequest(const char * buffer);
		~HttpRequest();

		std::string							const &getReqLine() const;
		std::string							const &getType() const;
		std::string							const &getLocation() const;
		std::string							const &getVersion() const;
		std::map<std::string, std::string>	const &getHeaders() const;
		std::string							const &getbody() const;
		bool								ContainsHead(std::string key, std::map<std::string, std::string> reqHeaders);
};

#endif
