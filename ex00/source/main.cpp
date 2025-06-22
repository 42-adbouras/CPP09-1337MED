/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:48:01 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/22 17:33:19 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main( int ac, char** av )
{
	(void) ac;
	BitcoinExchange::openFiles(av[1]);
	BitcoinExchange::processFiles();
	return (0);
}
