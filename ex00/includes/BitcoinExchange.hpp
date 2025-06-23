/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:01:59 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/23 17:50:31 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define BLUE	"\033[1;34m"
#define RED		"\033[1;31m"
#define GREEN	"\033[1;32m"
#define RESET	"\033[0m"

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
	static std::map<str, double>	_exchangeRates;
	static std::ifstream		_input;

	BitcoinExchange( void ) {}
	// BitcoinExchange( const BitcoinExchange& right ) {}
	~BitcoinExchange( void ) {}

	// BitcoinExchange&		operator=( const BitcoinExchange& right );
public:
	static void	openFiles( char* arg );
	static void	processFiles( void );
};
