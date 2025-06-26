/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:42:41 by adbouras          #+#    #+#             */
/*   Updated: 2025/06/25 21:58:56 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <limits>
#include <cstdlib> //+++++++

typedef std::string str;

class PmergeMe
{
private:
	PmergeMe( void );
	PmergeMe( const PmergeMe& right );
	~PmergeMe( void );
	PmergeMe&	operator=( const PmergeMe& right );
	
	static std::vector<int>	_vec;
	static std::deque<int>	_deq;
public:
	static void	sort( int ac, char** av );
};