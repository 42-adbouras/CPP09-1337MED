/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:20:24 by codespace         #+#    #+#             */
/*   Updated: 2025/06/24 12:22:27 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

std::stack<int>	RPN::_stack;

bool	isOperator( str& op )
{
	return (op == "+" || op == "-" || op == "*" || op == "/");
}

int	RPN::calculate( str& arg )
{
	std::stringstream	sstream(arg);
	str					token;

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
				if (x == 0)
					throw (RPN::DevidingByZeroException());
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
