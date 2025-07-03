/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:42:41 by adbouras          #+#    #+#             */
/*   Updated: 2025/07/03 13:06:25 by adbouras         ###   ########.fr       */
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
#define	INVALID_ARG RED "[PmergeMe::InvalidArgException]: "

typedef std::string			str;
typedef std::vector<int>	int_vec;
typedef std::deque<int>		int_deq;

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

