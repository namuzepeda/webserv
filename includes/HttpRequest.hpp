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

#include "URI.hpp"
#include "WebServ.hpp"

class HttpRequest
{
	private:

		URI			uri;
		std::map<std::string, std::string> headers;
		std::string	body;
		RequestType	type;

	public:

		static	HttpRequest *build(const std::string &buffer);

		HttpRequest();
		HttpRequest(URI const &uri, std::string body, RequestType type);
		virtual				~HttpRequest() {}

		URI 		const	&getURI(void) const;
		Config				*getHeaders(void);
		std::string	const	&getBody(void) const;
		RequestType 		getType(void);

};

#endif
