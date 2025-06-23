/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:01:55 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/23 16:33:13 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::map<str, double>	BitcoinExchange::_exchangeRates;
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
		double	val;

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
	double	lfValue;
	
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
		std::map<str, double>::iterator	it = _exchangeRates.lower_bound(date);
		if (it == _exchangeRates.begin() && it->first != date) {
			std::cerr << "Error: date too early => " << date << std::endl;
			continue ;
		}
		if (it == _exchangeRates.end() && it->first != date) {
			std::cerr << "Error: date not found => " << date << std::endl;
			continue ;
		}
		it--;
		std::cout << it->first << " => " << lfValue << " = " << it->second * lfValue;
		std::cout << " [" << it->second << " * " << lfValue << "]" << std::endl;

		// std::cout << ":" << date << ":" << " => " << ":" << value << ":" << std::endl;
	}
	
}
