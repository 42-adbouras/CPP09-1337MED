/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:01:55 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/22 17:59:24 by adbouras         ###   ########.fr       */
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

void	BitcoinExchange::processFiles( void )
{
	str		line, date, value;
	
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
		std::cout << ":" << date << ":" << " => " << ":" << value << ":" << std::endl;
	}
	
}
