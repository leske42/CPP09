/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:08 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/18 18:28:15 by mhuszar          ###   ########.fr       */
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

    cont_chain.display_list();
    
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
    bottom = (recursion_levels * 2 * (-1)); //lets try +etc here
    breakpoint = recursion_levels * (-1);
    // std::cout << "Bottom: " << bottom << " Breakpoint: " << breakpoint << " Levels: " << recursion_levels << std::endl;
    assemble();
}