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

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "URI.hpp"
#include "WebServ.hpp"

class HttpResponse
{
	private:

		URI			uri;
		Config		*headers;
		std::string	body;
		RequestType	type;

	public:

		HttpResponse(URI const &uri, std::string body, RequestType const &type);
		HttpResponse(HttpResponse const &copy);

		HttpResponse const	&operator=(HttpResponse const &copy);
		virtual				~HttpResponse() {}

		URI 		const	&getURI(void) const;
		Config				*getHeaders(void);
		std::string	const	&getBody(void) const;
		RequestType 		getType(void);

};


#endif
