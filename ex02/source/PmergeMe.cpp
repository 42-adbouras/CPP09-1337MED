/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:42:33 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/27 20:29:03 by adbouras         ###   ########.fr       */
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
void	mergeInsertSort( Type& con, size_t start, size_t end )
{
	if (end - start < 2) return ;
	size_t	mid = start + (end - start) / 2;

	mergeInsertSort(con, start, mid);
	mergeInsertSort(con, mid, end);

	Type	temp(con.begin() + start, con.begin() + end);
	size_t	i = 0, j = mid - start, k = start;

	while (i < mid - start && j < end - start)
	{
		if (temp[i] < temp[j])
			con[k++] = temp[i++];
		else
			con[k++] = temp[j++];
	}
	while (i < mid - start)
		con[k++] = temp[i++];
	while (j < end - start)
		con[k++] = temp[j++];
}

void	PmergeMe::sort( int ac, char** av )
{
	_vec = parseInput(ac, av);

	for (size_t i = 0; i < _vec.size(); i++) {
		std::cout << _vec[i] << " ";
	}
	mergeInsertSort(_vec, 0, _vec.size());
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
