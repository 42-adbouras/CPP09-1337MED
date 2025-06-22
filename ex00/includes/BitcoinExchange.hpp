/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:01:59 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/22 22:12:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <iomanip>
#include <limits>

typedef std::string			str;
typedef std::stringstream	sstream;

class BitcoinExchange
{
private:
	static std::map<str, float>	_exchangeRates;
	static std::ifstream		_input;

	BitcoinExchange( void ) {}
	// BitcoinExchange( const BitcoinExchange& right ) {}
	~BitcoinExchange( void ) {}

	// BitcoinExchange&		operator=( const BitcoinExchange& right );
public:
	static void	openFiles( char* arg );
	static void	processFiles( void );
};
