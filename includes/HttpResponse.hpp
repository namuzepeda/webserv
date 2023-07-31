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

#include "WebServ.hpp"

class HttpResponse
{
	private:

		std::map<std::string, std::string> headers;
		std::string	body;
		RequestType	type;

	public:

		HttpResponse(void);

		HttpResponse(std::string body, RequestType const &type);
		HttpResponse(HttpResponse const &copy);

		HttpResponse const	&operator=(HttpResponse const &copy);
		virtual				~HttpResponse() {}

		std::map<std::string, std::string> const	&getHeaders(void) const;
		std::string	const							&getBody(void) const;
		RequestType 								getType(void);

		std::string									toString(void);

};


#endif
