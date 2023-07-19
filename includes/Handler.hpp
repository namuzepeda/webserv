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

#pragma once

#include "IHandler.hpp"
#include <set>

class Handler: public IHandler
{
	protected:

		std::set<Handler*>		childs;
		Handler					*config;

	public:

		Handler(Config const &config);
		Handler(Handler const &copy);

		Handler const				&operator=(Handler const &copy);
		virtual						~Handler() {}

		virtual bool 				hasChilds();
		std::set<Handler*> const	&getChilds() const;

		Config const				&getConfig() const;

};
