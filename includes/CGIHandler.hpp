/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:10:27 by gamoreno          #+#    #+#             */
/*   Updated: 2023/10/10 17:47:27 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLER_HPP
# define CGIHANDLER_HPP

# include "WebServ.hpp"

class CGIHandler
{

	public:
		/*
		After check the extension of the request searching for CGI scripts
		exemple:
			resource = "/my_script.cgi";
			parameters = "param1=value1&param2=value2"
		*/
		CGIHandler(const &std::string resource, const &std::string parameters);
		CGIHandler( CGIHandler const & src );
		~CGIHandler();

		CGIHandler &		operator=( CGIHandler const & rhs );
		std::string			executeScript();

	private:
		const std::string _resource;
		const std::string _parameters;
};

// std::ostream &			operator<<( std::ostream & o, CGIHandler const & i );

#endif /* ****************************************************** CGIHANDLER_H */