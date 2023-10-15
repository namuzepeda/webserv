/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:19:33 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
#define HANDLER_H

#include "WebServ.hpp"

class Handler
{
	protected:

		std::vector<Handler *>		childs;
		Config						*config;

	public:

		Handler(Config *config);
		virtual							~Handler();

		bool 							hasChilds(void);
		std::vector<Handler *> 	const	&getChilds(void) const;
		void							addChild(Handler *handler);

		Config							*getConfig(void);
		void							setConfig(Config *config);

		virtual void	 				run(const HttpRequest &request) = 0;

};

#endif
