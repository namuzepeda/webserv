/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:12:08 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/20 20:12:08 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
#define LOGGER_H

#include "WebServ.hpp"

class Logger {

	private:
		int	fd;
		char *color;

	public:

		static Logger *info;

		Logger(std::string &filePath, const char *color);
		Logger(int fd, const char *color);
		~Logger();
		Logger(Logger const &src);
		Logger &operator=(Logger const &rhs);

		int		getFd();

		void	log(const char *msg, const char *color);
		void	log(const char *msg);

};

#endif

