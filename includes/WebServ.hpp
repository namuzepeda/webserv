/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:35:06 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/20 17:35:06 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>

enum class TokenType {
    Identifier,
    Value,
    BlockStart,
    BlockEnd,
    Semicolon,
    Invalid
};

struct Token {
    TokenType type;
    std::string value;
};
