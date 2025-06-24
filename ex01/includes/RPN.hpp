/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:17:23 by codespace         #+#    #+#             */
/*   Updated: 2025/06/24 12:33:25 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <sstream>
#include <exception>

#define INVALID_ARG "[RNP::InvalidArgumentException => "

typedef std::string str;

class RPN
{
private:
	RPN( void ) {}
	static std::stack<int>	_stack;
public:
	static int	calculate( str& arg );

	class NumberOfArgsException : public std::exception {
	public:
		const char*	what() const throw() {
			return ("[RPN::NotEnoughNumbersException]");
		}
	};
	class DevidingByZeroException : public std::exception {
	public:
		const char*	what() const throw() {
			return ("[RPN::DevidingByZeroException]");
		}
	};
	class InvalidArgException : public std::exception {
	private:
		std::string _arg;
		std::string _err;
	public:
		InvalidArgException( std::string& arg) : _arg(arg) {
			this->_err = "[RNP::InvalidArgumentException => " + this->_arg + "]";
		}
		~InvalidArgException() throw() {}
		const char*	what() const throw() {
			return (this->_err.c_str());
		}
	};
	class TokenLeftoverException : public std::exception {
	public:
		const char*	what() const throw() {
			return ("[RPN::TokenLeftoverException]");
		}
	};
};
