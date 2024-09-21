/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:06 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/21 20:00:37 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "PmergeVect.hpp"
#include "OperationInterrupt.hpp"
#include "MyList.hpp"
#include <sys/time.h>

#define MIL 1000000 //TODO: can i do define here?

void display_time(struct timeval& ts1, struct timeval& ts2)
{
    size_t total_micros1 = ts1.tv_sec * MIL + ts1.tv_usec;
    size_t total_micros2 = ts2.tv_sec * MIL + ts2.tv_usec;
    size_t diff_micros = total_micros2 - total_micros1;
    size_t sec = diff_micros / MIL;
    // size_t msec = 
    size_t usec = diff_micros % MIL;
    std::cout << sec << " seconds and " << usec << " microseconds." << std::endl;
}

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
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::deque : ";
    display_time(ts1, ts2);

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
    std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : ";
    display_time(ts1, ts2);
    return (0);
}