/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileUtils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:12:08 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/20 20:12:08 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "WebServ.hpp"


class FileUtils {

	public:

		static bool	fileExists(const std::string &fileName);
		static bool	canRead(const std::string &fileName);

};


#endif
