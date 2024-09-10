/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:08 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/10 12:32:35 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
    //cont_chain = MyList< std::deque<int> >;
}

PmergeMe::PmergeMe(int argc, char **argv)
{
    // std::cout << (*argv)[1] << std::endl;
    //depth = calculate_depth(argc) * 2 * (-1);
    //std::cout << "Levels: " << recursion_levels << std::endl;
    //cont_chain = MyList< std::deque<int> >;
    
    //cont_chain = new std::deque<int>[2];
    //cont_chain = MyList< std::deque<int> >(argc, argv);
    //intake_sequence(argc, argv);
    calculate_depth(argc);
    cont_chain.create_list_head(argc, argv);
    //cont_chain.setup_next_depth(); //do i need this? What's the issue?
    print_content(0);
    do_sort();
    // std::cout << "[0] content: ";
    // print_content(0);
    // std::cout << "[1] content: ";
    // print_content(1);
}

PmergeMe::~PmergeMe(void)
{
    //delete[] cont_chain;
}

// void PmergeMe::calculate_depth()
// {
    
// }

void PmergeMe::execute()
{
    return ;
}