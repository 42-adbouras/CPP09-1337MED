/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:42:41 by adbouras          #+#    #+#             */
/*   Updated: 2025/07/04 14:22:48 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <limits>
#include <algorithm>
#include <sys/time.h>

#define BLUE	"\033[1;34m"
#define RED		"\033[1;31m"
#define GREEN	"\033[1;32m"
#define RESET	"\033[0m"

#define USAGE RED "[PmergeMe::UsageException]: ./PmergeMe <Positive Integers>" RESET
#define	INVALID_ARG RED "[PmergeMe::InvalidArgException]: \""

typedef std::string			str;
typedef std::vector<int>	int_vec;
typedef std::deque<int>		int_deq;

template<typename Type>
Type	fordJohnson( Type& con );

double	calculateTime(struct timeval t_start, struct timeval t_end);

class PmergeMe
{
private:
	PmergeMe( void );
	PmergeMe( const PmergeMe& right );
	~PmergeMe( void );
	PmergeMe&	operator=( const PmergeMe& right );
	
	static int_vec	_vec;
	static int_deq	_deq;
public:
	static void	init( int ac, char** av );
	static void	sort( void );

	class UsageException : public std::exception {
	public:
		const char*	what() const throw();
	};
	class InvalidArgException : public std::exception {
	private:
		str	_arg, _err;
	public:
		InvalidArgException( str& arg );
		~InvalidArgException( void ) throw();
		const char*	what() const throw();
	};
};

template<typename Type>
Type	jacobSthal( int size )
{
	Type	seq;
	int		next;

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

template<typename Type>
Type	genInsertOrder( size_t size )
{
	Type				order;
	std::vector<bool>	inserted(size, false);

	Type	jacob = jacobSthal<Type>(size);

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
bool	isSorted( const Type& con )
{
	if (con.size() < 2) return (true);

	for (size_t i = 0; i < con.size() - 1; i++) {
		if (con[i] > con[i + 1]) return (false);
	}
	return (true);
}

template<typename Type>
double	getBenckmark( Type& con )
{
	struct timeval	t_start, t_end;

	if (isSorted(con)) return (0);

	gettimeofday(&t_start, NULL);
	con = fordJohnson<Type>(con);
	gettimeofday(&t_end, NULL);

	return (calculateTime(t_start, t_end));	
}

template<typename Type>
void	printStatus( const Type& con, bool isVec, double con_dur )
{
	str	container = isVec ? "[std::vector]" : "[std::deque ]";

	if (isSorted<Type>(con)) {
		container += ": ";
		std::cout << GREEN "Time to process a range of " << con.size() \
		<< " elements with " << container << con_dur << " us." RESET << std::endl;
	} else {
		std::cout << RED << container << " is not sorted!" RESET << std::endl;
	}
}
