/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:42:33 by adbouras          #+#    #+#             */
/*   Updated: 2025/07/04 14:33:12 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int_vec	PmergeMe::_vec;
int_deq	PmergeMe::_deq;

PmergeMe::PmergeMe( void ) { }
PmergeMe::~PmergeMe( void ) { }
PmergeMe::PmergeMe( const PmergeMe& right ) { static_cast<void>(right); }
PmergeMe&	PmergeMe::operator=( const PmergeMe& right )
{
	static_cast<void>(right); return(*this);
}

bool	isNum( const str& num )
{
	for (size_t i = 0; i < num.size(); i++) {
		if(!std::isdigit(num[i])) return (false);
	}
	return (true);
}

int_vec	parseInput( int ac, char** av )
{
	int_vec	arr;
	long	num;
	str		arg;

	for (int i = 1; i < ac; i++) {
		arg = av[i];
		if(!isNum(arg) || !arg.size()) throw (PmergeMe::InvalidArgException(arg));
		num = std::strtol(arg.c_str(), NULL, 10);
		if (num > std::numeric_limits<int>::max())
			throw (PmergeMe::InvalidArgException(arg));
		arr.push_back(static_cast<int>(num));
	}
	return (arr);
}

template<typename Type>
Type	fordJohnson( Type& con )
{
	if (con.size() < 2) return(con) ;

	Type	smalls, larges, sorted;

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

	sorted = fordJohnson<Type>(larges);

	Type	inOrder = genInsertOrder<Type>(smalls.size());

	for (size_t i = 0; i < inOrder.size(); i++) {
		int idx = inOrder[i];
		binaryInsert(sorted, smalls[idx]);
	}

	if (odd)
		binaryInsert(sorted, rem);
	return (sorted);
}

void	PmergeMe::init( int ac, char** av )
{
	_vec = parseInput(ac, av);
	_deq = int_deq(_vec.begin(), _vec.end());

	std::cout << "before: ";
	for (size_t i = 0; i < _vec.size(); i++) {
		std::cout << _vec[i] << " ";
	}
	std::cout << std::endl;
}

double	calculateTime(struct timeval t_start, struct timeval t_end)
{
	return (((t_end.tv_sec - t_start.tv_sec) * 1e6) + (t_end.tv_usec - t_start.tv_usec));
}

void	PmergeMe::sort( void )
{
	double vec_dur = getBenckmark<int_vec>(_vec);
	double deq_dur = getBenckmark<int_deq>(_deq);

	std::cout << "after : ";
	for (size_t i = 0; i < _vec.size(); i++) {
		std::cout << _vec[i] << " ";
	} std::cout << std::endl;

	printStatus<int_vec>(_vec, true,  vec_dur);
	printStatus<int_deq>(_deq, false, deq_dur);
}

const char*	PmergeMe::UsageException::what() const throw()
{
	return (USAGE);
}

PmergeMe::InvalidArgException::InvalidArgException( str& arg ) : _arg(arg)
{
	_err = INVALID_ARG + _arg + "\"" + RESET;
}

PmergeMe::InvalidArgException::~InvalidArgException( void ) throw() { }

const char*	PmergeMe::InvalidArgException::what() const throw()
{
	return(_err.c_str());
}
