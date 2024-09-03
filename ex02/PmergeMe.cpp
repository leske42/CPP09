/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:08 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/03 15:40:56 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
    
}

PmergeMe::PmergeMe(int argc, char ***argv)
{
    std::cout << (*argv)[1] << std::endl;
    calculate_depth(argc);
    cont_chain = new std::deque<int>[2];
    intake_sequence(argc, argv);
    create_sequence();
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