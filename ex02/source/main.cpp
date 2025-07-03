/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:41:13 by adbouras          #+#    #+#             */
/*   Updated: 2025/07/03 13:56:20 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main( int ac, char** av )
{
	try {
		if (ac < 2) throw (PmergeMe::UsageException());
		PmergeMe::init(ac, av);
		PmergeMe::sort();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);	
}
