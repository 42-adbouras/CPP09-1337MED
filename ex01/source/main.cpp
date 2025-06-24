/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:13:59 by codespace         #+#    #+#             */
/*   Updated: 2025/06/24 12:53:28 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main( int ac, char** av)
{

	try {
		if (ac != 2)
			throw (RPN::UsageException());

		str	input(av[1]);
		int result = RPN::calculate(input);
		std::cout << "Result: " << result << "." << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}