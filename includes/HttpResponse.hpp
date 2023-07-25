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

#pragma once

#include "URI.hpp"

enum RequestType {
	GET,
	POST,
	DELETE
};

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
		Config		const	&headers(void) const;
		std::string	const	&getBody(void) const;
		RequestType 		getType(void);

};
