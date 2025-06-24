/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:13:59 by codespace         #+#    #+#             */
/*   Updated: 2025/06/24 17:49:29 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <map>

int	main( int ac, char** av)
{
	try {
		if (ac != 2) throw (RPN::UsageException());

		str	input(av[1]);
		int result = RPN::calculate(input);

		std::cout << "Result: " << result << "." << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
