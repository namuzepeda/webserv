/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 21:03:32 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
#define SERVER_H

#include "ServerHandler.hpp"

class Server
{
	private:

		ServerHandler		*handler;

		std::string			host;
		std::vector<int>	ports;
		std::string			rootFolder;

	public:

		Server(ServerHandler const &handler);
		Server(Server const &copy);

		Server const	&operator=(Server const &copy);
		virtual			~Server() {}

		ServerHandler		const	&getHandler(void) const;
		std::string			const	&getHost(void) const;
		std::vector<int>	const	&getPorts(void);
		std::string			const	&getRoot() const;
};


#endif
