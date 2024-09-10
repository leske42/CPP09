/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:08 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/10 19:09:49 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{

}

PmergeMe::PmergeMe(int argc, char **argv)
{
    do_sort(argc, argv);

    cont_chain.display_list();
    // std::cout << "[0] content: ";
    // print_content(0);
    // std::cout << "[1] content: ";
    // print_content(1);
}

PmergeMe::~PmergeMe(void)
{

}

void PmergeMe::do_sort(int argc, char **argv)
{
    calculate_depth(argc);
    cont_chain.init_list_head(argc, argv);
    bottom = recursion_levels * 2 * (-1);
    breakpoint = recursion_levels * (-1);
    assemble();
}