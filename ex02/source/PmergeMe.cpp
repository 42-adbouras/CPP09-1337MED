/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:42:33 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/28 15:27:59 by adbouras         ###   ########.fr       */
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
		if(!isNum(arg)) throw (PmergeMe::InvalidArgException(arg));
		num = std::strtol(arg.c_str(), NULL, 10);
		if (num > std::numeric_limits<int>::max())
			throw (PmergeMe::InvalidArgException(arg));
		arr.push_back(static_cast<int>(num));
	}
	return (arr);
}

template<typename Type>
Type	genJS( size_t count )
{
	Type	indices;

	size_t	i = 1, j = 3;
	if (count > 0) indices.push_back(0);
	if (count > 1) indices.push_back(1);
	
	while (indices.size() < count) {
		size_t next = j + 2 * i;
		if (next >= count) break ;
		indices.push_back(next);
		i = j;
		j = next;
	}

	for ( size_t idx = 0; idx < count; idx++) {
		if (std::find(indices.begin(), indices.end(), idx) == indices.end())
			indices.push_back(idx);
	}
	return (indices);
}

template<typename Type>
void	fordJohnson( Type& con )
{
	if (con.size() < 2) return ;

	Type	smalls, larges;

	for (size_t i = 0; i + 1 < con.size(); i += 2) {
		int	x = con[i], y = con[i + 1];
		if (x < y) {
			smalls.push_back(x);
			larges.push_back(y);
		} else {
			smalls.push_back(y);
			larges.push_back(x);
		}
	}
	bool	odd = (con.size() % 2 != 0);
	int		rem = odd ? con.back() : -1;
	
	fordJohnson(larges);
	
	Type	jacobStahl = genJS<Type>(smalls.size());
	for (size_t i = 0; i < jacobStahl.size(); i++) {
		if (i < smalls.size()) {
			typename Type::iterator it = std::lower_bound(larges.begin(), larges.end(), smalls[i]);
			larges.insert(it, smalls[i]);
		}
	}

	if (odd) {
		typename Type::iterator it = std::lower_bound(larges.begin(), larges.end(), rem);
		larges.insert(it, rem);
	}
	con = larges;
}

void	PmergeMe::sort( int ac, char** av )
{
	_vec = parseInput(ac, av);

	for (size_t i = 0; i < _vec.size(); i++) {
		std::cout << _vec[i] << " ";
	}
	fordJohnson(_vec);
	std::cout << std::endl;
	for (size_t i = 0; i < _vec.size(); i++) {
		std::cout << _vec[i] << " ";
	}
	std::cout << std::endl;
}

const char*	PmergeMe::UsageException::what() const throw()
{
	return (USAGE);
}

PmergeMe::InvalidArgException::InvalidArgException( str& arg ) : _arg(arg)
{
	_err = INVALID_ARG + _arg + RESET;
}

PmergeMe::InvalidArgException::~InvalidArgException( void ) throw() { }

const char*	PmergeMe::InvalidArgException::what() const throw()
{
	return(_err.c_str());
}
