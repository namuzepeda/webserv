/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHolder.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 21:03:32 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HOLDER_H
#define SERVER_HOLDER_H

#include "Config.hpp"

class ServerHolder : public Config
{
	public:

		ServerHolder(void);
		ServerHolder(ServerHolder const &copy);

		ServerHolder const	&operator=(ServerHolder const &copy);

		virtual				~ServerHolder();

		bool				hasServerName();
		std::string			getServerName();

		virtual ContextType			getType();
};

#endif
