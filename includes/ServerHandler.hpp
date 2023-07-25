/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:22:03 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include "Handler.hpp"

class ServerHandler : public Handler
{
	public:

		ServerHandler(Config const &config);
		ServerHandler(ServerHandler const &copy);

		ServerHandler const	&operator=(ServerHandler const &copy);

		~ServerHandler();

		void			run(const HttpRequest &request, const HttpResponse &response);
};

#endif
