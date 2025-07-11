/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:20:24 by codespace         #+#    #+#             */
/*   Updated: 2025/06/25 14:41:48 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

std::stack<int>	RPN::_stack;

RPN::RPN( void ) { }
RPN::~RPN( void ) { }
RPN::RPN( const RPN& right ) { static_cast<void>(right); }
RPN&	RPN::operator=( const RPN& right )
{
	static_cast<void>(right); return (*this);
}

static bool	isOperator( const str& op )
{
	return (op == "+" || op == "-" || op == "*" || op == "/");
}

int	RPN::calculate( const str& arg )
{
	strstream	sstream(arg);
	str			token;

	while (sstream >> token)
	{
		if (token.length() == 1 && std::isdigit(token[0]))
			_stack.push(token[0] - '0');
		else if (isOperator(token)) {
			if (_stack.size() < 2)
				throw (RPN::NumberOfArgsException());

			int	x = _stack.top(); _stack.pop();
			int	y = _stack.top(); _stack.pop();
			if (token == "+") _stack.push(y + x);
			else if (token == "-") _stack.push(y - x);
			else if (token == "*") _stack.push(y * x);
			else if (token == "/") {
				if (x == 0) throw (RPN::DevidingByZeroException());
				_stack.push(y / x);
			}
		} else {
			throw (RPN::InvalidArgException(token));
		}
	}
	if (_stack.size() != 1)
		throw (RPN::TokenLeftoverException());
	return (_stack.top());
}

const char*	RPN::UsageException::what() const throw()
{
	return (USAGE);
}

const char*	RPN::NumberOfArgsException::what() const throw()
{
	return (ARGS_NUM);
}

const char*	RPN::DevidingByZeroException::what() const throw()
{
	return (DEV_BY_ZERO);
}

RPN::InvalidArgException::InvalidArgException( str& arg )  : _arg(arg)
{
	this->_err = INVALID_ARG + this->_arg + RESET;
}

RPN::InvalidArgException::~InvalidArgException( void ) throw() { }

const char*	RPN::InvalidArgException::what() const throw()
{
	return (this->_err.c_str());
}

const char*	RPN::TokenLeftoverException::what() const throw()
{
	return (TOKEN_LEFT);
}
