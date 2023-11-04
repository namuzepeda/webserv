/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:12:08 by nmunoz            #+#    #+#             */
/*   Updated: 2023/10/16 19:24:09 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "WebServ.hpp"


class ClientConnection {
	
	public:

		static std::map<int, std::string> requests;

		static bool			isChunkedRequest(int socket);
		static bool			isRequestCompleted(int socket);
		static std::string	getBuffer(int socket);
		static void    		deleteBuffer(int socket);
		static bool			hasBuffer(int socket);

		

};


#endif
