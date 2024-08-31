/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:08 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/31 19:17:45 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
    
}

PmergeMe::PmergeMe(int argc, char **argv)
{
    calculate_depth(argc);
    cont_chain = new std::deque<int>;
    intake_sequence(argc, argv);
}

PmergeMe::~PmergeMe(void)
{
    delete[] cont_chain;
}

// void PmergeMe::calculate_depth()
// {
    
// }

void PmergeMe::execute()
{
    return ;
}