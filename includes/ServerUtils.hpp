/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:12:08 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/20 20:12:08 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include "Server.hpp"
#include <iostream>
#include "HttpRequest.hpp"


class ServerUtils {

	public:

		static bool doesRequestApply(Server &server, HttpRequest &request);

};

#endif

