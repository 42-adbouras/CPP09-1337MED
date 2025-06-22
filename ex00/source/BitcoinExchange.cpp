/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:01:55 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/22 22:43:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::map<str, float>	BitcoinExchange::_exchangeRates;
std::ifstream			BitcoinExchange::_input;

void	BitcoinExchange::openFiles( char *arg )
{
	std::ifstream	data("cpp_09/data.csv");
	_input.open(arg);

	if (!arg || !_input.is_open() || !data.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		exit(1);
	}
	str		line;

	std::getline(data, line);
	while (std::getline(data, line))
	{
		str		key;
		float	val;

		key = line.substr(0, 10);
		val = std::strtof((line.substr(11, line.size() - 1)).c_str(), NULL);
		_exchangeRates[key] = val;
	}
	data.close();
}

bool	validDate( str& date )
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	return (true);
}

bool	isWhitespace(unsigned char ch)
{
	return std::isspace(ch);
}

void	BitcoinExchange::processFiles( void )
{
	str		line, date, value;
	float	lfValue;
	
	std::getline(_input, line);
	std::getline(_input, line);
	while (std::getline(_input, line))
	{
		if (line.find(" | ") == std::string::npos) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}
		date  = line.substr(0, line.find(" | "));
		value = line.substr(line.find(" | ") + 3);
		if (!validDate(date)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;	
		}

		sstream	vStream(value);
		vStream >> lfValue;
		if (vStream.fail() || !vStream.eof()) {
			std::cerr << "Error: bad value => " << value << std::endl;
			continue ;
		}
		if (lfValue < 0) {
			std::cerr << "Error: not a positive number." << std::endl;
			continue ;
		}
		if (lfValue > std::numeric_limits<int>::max()) {
			std::cerr << "Error: too large a number. " << std::endl;
			continue ;
		}
		std::map<str, float>::iterator	it = _exchangeRates.lower_bound(date);
		std::cout << date << " => [" << it->first << "]" << std::endl;

		// std::cout << ":" << date << ":" << " => " << ":" << value << ":" << std::endl;
	}
	
}
