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

#include "WebServ.hpp"

class Server
{
	private:

		static short		counter;

		short				id;

		ServerHandler		*handler;

		std::string			host;
		std::vector<int>	ports;
		std::string			rootFolder;

		int					serverSocket;
		sockaddr_in 		socketAddr;

	public:

		Server(ServerHandler *handler);

		virtual			~Server() {}

		ServerHandler				*getHandler(void);
		std::string			const	&getHost(void) const;
		std::vector<int>	const	&getPorts(void);
		std::string			const	&getRoot() const;

		InitType 					init(int tryTimes);
		InitType					test(int times);
};

#endif
