/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:01:55 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/25 16:42:44 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::map<str, double>	BitcoinExchange::_exchangeRates;
std::ifstream			BitcoinExchange::_input;

BitcoinExchange::BitcoinExchange( void ) { }
BitcoinExchange::BitcoinExchange( const BitcoinExchange& right ) { static_cast<void>(right); }
BitcoinExchange::~BitcoinExchange( void ) { }
BitcoinExchange&	BitcoinExchange::operator=( const BitcoinExchange& right )
{
	static_cast<void>(right); return (*this);
}

void	BitcoinExchange::openFiles( char *arg )
{
	std::ifstream	data(DATA_FILE);
	str				line;

	_input.open(arg);
	if (!arg || !_input.is_open()) throw (BitcoinExchange::BadFileExcption(arg));
	if (!data.is_open()) throw (BitcoinExchange::BadFileExcption(DATA_FILE));

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
	str		day, month;
	int		value;

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	month = date.substr(5, 2);
	day   = date.substr(8, 2);

	sstream	stream(month);
	stream >> value;

	if (value < 1 || value > 12)
		return (false);

	stream.clear(); stream.str(day); value = 0;
	stream >> value;

	if (value < 1 || value > 31)
		return (false);
	return (true);
}

void	BitcoinExchange::processFiles( void )
{
	str		line, date, value;
	double	ldValue;
	
	std::getline(_input, line);
	std::cout << std::left << std::setw(13) << "   Date" \
	<< std::left << std::setw(15) << "   Amount" \
	<< "Change" << std::endl;
	while (std::getline(_input, line))
	{
		if (!line.length()) continue ;
		if (line.find(" | ") == std::string::npos) {
			std::cerr << BAD_INPUT << line << RESET << std::endl;
			continue ;
		}
		date  = line.substr(0, line.find(" | "));
		value = line.substr(line.find(" | ") + 3);
		if (!validDate(date)) {
			std::cerr << BAD_INPUT << line << RESET << std::endl;
			continue ;	
		}

		sstream	vStream(value);
		vStream >> ldValue;
		if (vStream.fail() || !vStream.eof()) {
			std::cerr << BAD_VALUE << value << RESET << std::endl;
			continue ; 
		}
		if (ldValue < 0) {
			std::cerr << NOT_POSITIVE << std::endl;
			continue ;
		}
		if (ldValue > 1000) {
			std::cerr << LARGE_NUM << std::endl;
			continue ;
		}
		std::map<str, double>::iterator	it = _exchangeRates.lower_bound(date);

		if (it == _exchangeRates.begin() && it->first != date) {
			std::cerr << EARLY_DATE << date << RESET << std::endl;
			continue ;
		}
		if (it == _exchangeRates.end()) it--;
	
		std::cout << std::left << std::setw(12) << it->first << "➜     ";
		std::cout << std::left << std::setw(6)  << ldValue   << "=    ";
		std::cout << it->second * ldValue << std::endl;
	}
}

BitcoinExchange::BadFileExcption::BadFileExcption( const str& arg ) : _arg(arg)
{
	this->_err = BAD_FILE + _arg + RESET;
}

const char*	BitcoinExchange::BadFileExcption::what() const throw()
{
	return (this->_err.c_str());
}

const char*	BitcoinExchange::UsageExcption::what() const throw()
{
	return (USAGE);
}

BitcoinExchange::BadFileExcption::~BadFileExcption( void ) throw() { }
