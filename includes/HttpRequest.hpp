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
		Config		headers;
		std::string	body;
		RequestType	type;

	public:

		HttpRequest(URI const &uri, std::string body, RequestType const &type);
		HttpRequest(HttpRequest const &copy);

		HttpRequest const	&operator=(HttpRequest const &copy);
		virtual				~HttpRequest() {}

		URI 		const	&getURI(void) const;
		Config		const	&getHeaders(void) const;
		std::string	const	&getBody(void) const;
		RequestType 		getType(void);

};

#endif
