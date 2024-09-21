/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:06 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/21 18:53:58 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "PmergeVect.hpp"
#include "OperationInterrupt.hpp"
#include "MyList.hpp"
#include <sys/time.h>

int main(int argc, char **argv)
{
    if (argc == 1)
        return (0);
    struct timeval ts1;
    struct timeval ts2;
    gettimeofday(&ts1, NULL);
    try
    {
        PmergeMe hehe(argc, argv);
    }
    catch (OperationInterrupt& e)
    {
        if (e.primed)
        {
            std::cerr << "Error" << std::endl;
            return (-1);
        }
    }
    gettimeofday(&ts2, NULL);
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque : " << ts2.tv_sec - ts1.tv_sec;
    std::cout << " seconds " << ts2.tv_usec - ts1.tv_usec << " microseconds." << std::endl;

    gettimeofday(&ts1, NULL);
    try
    {
        PmergeVect hihi(argc, argv);
    }
    catch (OperationInterrupt& e)
    {
        if (e.primed)
        {
            std::cerr << "Error" << std::endl;
            return (-1);
        }
    }
    gettimeofday(&ts2, NULL);
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << ts2.tv_sec - ts1.tv_sec;
    std::cout << " seconds " << ts2.tv_usec - ts1.tv_usec << " microseconds." << std::endl;
    return (0);
}