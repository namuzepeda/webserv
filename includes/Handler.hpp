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

#include "IHandler.hpp"
#include <set>

class Handler: public IHandler
{
	protected:

		std::set<Handler*>		childs;
		Config					config;

	public:

		Handler(Config const &config);
		Handler(Handler const &copy);

		Handler const				&operator=(Handler const &copy);
		virtual						~Handler() {}

		virtual bool 				hasChilds();
		std::set<IHandler> 	const	&getChilds() const;

		Config const				&getConfig() const;

		virtual	ContextType			getType()						= 0;
		virtual void	 			run(const HttpRequest &request, const HttpResponse &response) = 0;

};

#endif
