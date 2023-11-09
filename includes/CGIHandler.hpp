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
		static std::string getResponse(HttpRequest &request, const Server *server);
};

// std::ostream &			operator<<( std::ostream & o, CGIHandler const & i );

#endif /* ****************************************************** CGIHANDLER_H */