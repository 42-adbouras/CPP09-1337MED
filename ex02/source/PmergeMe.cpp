/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:42:33 by adbouras          #+#    #+#             */
/*   Updated: 2025/07/03 12:34:56 by adbouras         ###   ########.fr       */
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

bool	isNum( const str& num )
{
	for (size_t i = 0; i < num.size(); i++) {
		if(!std::isdigit(num[i])) return (false);
	}
	return (true);
}

std::vector<int>	parseInput( int ac, char** av )
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


std::vector<int>	jacobSthal(int size)
{
	std::vector<int>	seq;
	int 				next;

	seq.push_back(0);
	if (size == 0) return (seq);
	seq.push_back(1);

	while (seq.back() < size) {
		next = seq[seq.size() - 1] + 2 * seq[seq.size() - 2];
		if (next >= size) break ;
		seq.push_back(next);
	}

	return (seq);
}

std::vector<int>	genInsertOrder( size_t size )
{
	std::vector<int>	order;
	std::vector<bool>	inserted(size, false);

	std::vector<int>	jacob = jacobSthal(size);

	for (size_t i = 1; i < jacob.size(); i++) {
		size_t idx = jacob[i] - 1;
		if (idx < size && !inserted[idx]) {
			order.push_back(idx);
			inserted[idx] = true;
		}
	}
	
	for (size_t i = 0; i < size; i++) {
		if (!inserted[i])
			order.push_back(i);
	}
	return (order);
}

template<typename Type>
void	binaryInsert( Type& sorted, int val )
{
	typename Type::iterator	pos;

	pos = std::lower_bound(sorted.begin(), sorted.end(), val);
	sorted.insert(pos, val);
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

	sorted = fordJohnson(larges);

	std::vector<int>	inOrder = genInsertOrder(smalls.size());

	for (size_t i = 0; i < inOrder.size(); i++) {
		int idx = inOrder[i];
		binaryInsert(sorted, smalls[idx]);
	}
	
	if (odd)
		binaryInsert(sorted, rem);
	return (sorted);
}

template<typename Type>
bool	isSorted( const Type& con )
{
	if (con.empty()) return (false);

	for (size_t i = 0; i < con.size() - 1; i++) {
		if (con[i] > con[i + 1]) return (false);
	}
	return (true);
}

void	PmergeMe::init( int ac, char** av )
{
	_vec = parseInput(ac, av);
	_deq = std::deque<int>(_vec.begin(), _vec.end());

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
	struct timeval	t_start, t_end;

	gettimeofday(&t_start, NULL);
	_vec = fordJohnson(_vec);
	gettimeofday(&t_end, NULL);
	double	vec_dur = calculateTime(t_start, t_end);

	gettimeofday(&t_start, NULL);
	_deq = fordJohnson(_deq);
	gettimeofday(&t_end, NULL);
	double	deq_dur = calculateTime(t_start, t_end);
	
	std::cout << "after : ";
	for (size_t i = 0; i < _vec.size(); i++) {
		std::cout << _vec[i] << " ";
	} std::cout << std::endl;

	if (isSorted(_vec)) {
		std::cout << GREEN "Time to process a range of " << _vec.size() \
		<< " elements with [std::vector]: " << vec_dur << " us." RESET << std::endl;
	} else {
		std::cout << RED "[std::vector] is not sorted!" RESET << std::endl;
	} if (isSorted(_deq)) {
		std::cout << GREEN "Time to process a range of " << _deq.size() \
		<< " elements with [std::deque ]: " << deq_dur << " us." RESET << std::endl;
	} else {
		std::cout << RED "[std::deque] is not sorted!" RESET << std::endl;
	}
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
