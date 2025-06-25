/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:23 by codespace         #+#    #+#             */
/*   Updated: 2025/06/25 14:18:18 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <sstream>
#include <exception>

#define BLUE	"\033[1;34m"
#define RED		"\033[1;31m"
#define GREEN	"\033[1;32m"
#define RESET	"\033[0m"

#define INVALID_ARG RED "[RNP::InvalidArgumentException] ➜ "
#define USAGE RED "[RPN::UsageException]: ./RPN \"<expressions>\"" RESET
#define ARGS_NUM RED "[RPN::NotEnoughNumbersException]" RESET
#define DEV_BY_ZERO RED "[RPN::DevidingByZeroException]" RESET
#define TOKEN_LEFT RED "[RPN::TokenLeftoverException]" RESET

typedef std::string 		str;
typedef std::stringstream	strstream;

class RPN
{
private:
	static std::stack<int>	_stack;
	
	RPN( void );
	RPN( const RPN& right );
	~RPN( void );
	RPN&	operator=( const RPN& right );
	
public:
	static int	calculate( const str& arg );

	class UsageException : public std::exception {
	public:
		const char*	what() const throw();
	};
	class NumberOfArgsException : public std::exception {
	public:
		const char*	what() const throw();
	};
	class DevidingByZeroException : public std::exception {
	public:
		const char*	what() const throw();
	};
	class InvalidArgException : public std::exception {
	private:
		str _arg;
		str _err;
	public:
		InvalidArgException( str& arg );
		~InvalidArgException( void ) throw();
		const char*	what() const throw();
	};
	class TokenLeftoverException : public std::exception {
	public:
		const char*	what() const throw();
	};
};
