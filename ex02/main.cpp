/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:06 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/06 15:34:53 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "OperationInterrupt.hpp"
#include "MyList.hpp"

int main(int argc, char **argv)
{
    try
    {
        PmergeMe hehe(argc, argv);
    }
    catch (OperationInterrupt& e)
    {
        if (e.primed)
            std::cerr << "Error" << std::endl;
    }
    return (0);
}