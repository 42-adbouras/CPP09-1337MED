/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:13:59 by codespace         #+#    #+#             */
/*   Updated: 2025/06/24 11:43:02 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main( int ac, char** av)
{
	if (ac != 2)
		std::cerr << "Usage: ./RPN <expression>" << std::endl;
	str	input(av[1]);

	try {
		std::cout << RPN::calculate(input) << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}