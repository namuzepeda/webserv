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

#include "Server.hpp"

class URI
{
	private:

		std::string		host;
		int				port;
		std::string		path;
		std::string		query;
		std::string		fragment;

	public:

		URI(std::string &host, int port, std::string path, std::string query, std::string fragment);
		URI(URI const &copy);

		URI const	&operator=(URI const &copy);
		virtual			~URI() {}

		std::string const	&getHost() const;
		int					getPort();
		std::string const	&getPath() const;
		std::string const	&getQuery() const;
		std::string const	&getFragment() const;

};
