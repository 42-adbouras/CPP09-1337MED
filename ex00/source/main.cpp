/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:48:01 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/25 14:15:20 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main( int ac, char** av )
{
	try {
		if (ac < 2) throw BitcoinExchange::UsageExcption();
		BitcoinExchange::openFiles(av[1]);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
	BitcoinExchange::processFiles();
	return (0);
}
