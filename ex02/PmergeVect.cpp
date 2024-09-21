/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeVect.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:29:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/21 18:38:57 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeVect.hpp"

PmergeVect::PmergeVect(void)
{

}

PmergeVect::PmergeVect(int argc, char **argv)
{
    sequence.resize(argc);
    
    do_sort(argc, argv);

    cont_chain.display_list();
    
    if (COUNT)
        std::cout << std::endl << "Number of comparisons: " << comp << std::endl;
}

PmergeVect::~PmergeVect(void)
{

}

void PmergeVect::do_sort(int argc, char **argv)
{
    calculate_depth(argc);
    cont_chain.init_list_head(argc, argv);
    bottom = (recursion_levels * 2 * (-1));
    breakpoint = recursion_levels * (-1);
    assemble();
}