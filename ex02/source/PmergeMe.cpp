/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:42:33 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/25 22:04:02 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::vector<int> PmergeMe::_vec;
std::deque<int>  PmergeMe::_deq;

PmergeMe::PmergeMe( void ) { }
PmergeMe::~PmergeMe( void ) { }
PmergeMe::PmergeMe( const PmergeMe& right ) { static_cast<void>(right); }
PmergeMe&	PmergeMe::operator=( const PmergeMe& right )
{
	static_cast<void>(right); return(*this);
}

static bool	isNum( const str& num )
{
	for (size_t i = 0; i < num.size(); i++) {
		if(!std::isdigit(num[i])) return (false);
	}
	return (true);
}

static std::vector<int>	parseInput( int ac, char** av )
{
	std::vector<int>	arr;
	long				num;
	for (int i = 1; i < ac; i++) {
		str	arg = av[i];
		if(!isNum(arg)) {
			std::cout << "nan: " << arg << std::endl;
			exit(1); // +++++++++++
		}
		num = std::strtol(arg.c_str(), NULL, 10);
		if (num > std::numeric_limits<int>::max()) exit(1); // ++++++++++++
		arr.push_back(static_cast<int>(num));
	}
	return (arr);
}

void	PmergeMe::sort( int ac, char** av )
{
	_vec = parseInput(ac, av);
	for (size_t i = 0; i < _vec.size(); i++) {
		std::cout << _vec[i] << " ";
	}
	std::cout << std::endl;
}