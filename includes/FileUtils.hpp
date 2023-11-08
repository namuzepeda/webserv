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

		static bool			fileExists(const std::string &fileName);
		static bool			fileExists(const std::string &path, const std::string &fileName);
		static bool			canRead(const std::string &fileName);
		static bool			canRead(const std::string &path, const std::string &fileName);
		static std::string	getFileData(const std::string &fileName);
		static std::string	getFileData(const std::string &path, const std::string &fileName);
		static bool  		isDirectory(const std::string &path);
		static bool 		canWrite(const std::string &fileName);

};


#endif
