/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:01:59 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/25 14:16:32 by adbouras         ###   ########.fr       */
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
#include <exception>

#define DATA_FILE "cpp_09/data.csv"
#define BAD_INPUT RED "\nError: bad input ➜ "
#define BAD_VALUE RED "\nError: bad value ➜ "
#define NOT_POSITIVE RED "\nError: not a positive number." RESET
#define LARGE_NUM RED "\nError: too large a number." RESET
#define EARLY_DATE RED "\nError: date too early ➜ "
#define BAD_FILE RED "[BitcoinExchange::CouldNotOpenFileException]: "
#define USAGE RED "[BitcoinExchange::UsageException]: ./btc <input.txt>" RESET

typedef std::string			str;
typedef std::stringstream	sstream;

class BitcoinExchange
{
private:
	static std::map<str, double>	_exchangeRates;
	static std::ifstream			_input;

	BitcoinExchange( void );
	BitcoinExchange( const BitcoinExchange& right );
	~BitcoinExchange( void );
	BitcoinExchange&	operator=( const BitcoinExchange& right );

public:
	static void	openFiles( char* arg );
	static void	processFiles( void );

	class UsageExcption : public std::exception {
		const char*	what() const throw();
	};
	class BadFileExcption : public std::exception {
	private:
		str	_arg;
		str	_err;
	public:
		~BadFileExcption( void ) throw();
		BadFileExcption( const str& arg );
		const char*	what() const throw();
	};
};
