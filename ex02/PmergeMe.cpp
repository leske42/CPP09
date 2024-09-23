/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:08 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/21 19:15:10 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{

}

PmergeMe::PmergeMe(int argc, char **argv)
{
    sequence.resize(argc);
    
    do_sort(argc, argv);

    std::cout << "After:   ";
    cont_chain.print_content(0);
    
    if (COUNT)
        std::cout << std::endl << "Number of comparisons: " << comp << std::endl;
}

PmergeMe::~PmergeMe(void)
{

}

void PmergeMe::do_sort(int argc, char **argv)
{
    calculate_depth(argc);
    cont_chain.init_list_head(argc, argv);
    bottom = (recursion_levels * 2 * (-1));
    breakpoint = recursion_levels * (-1);
    std::cout << "Before:  ";
    cont_chain.print_content(0);
    assemble();
}