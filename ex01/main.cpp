/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:52:20 by mhuszar           #+#    #+#             */
/*   Updated: 2024/10/05 11:46:21 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "OperationInterrupt.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Please provide the argument as one string" << std::endl;
        return (0);
    }
    try
    {
        std::string input = argv[1];
        RPN hehe(input);
    }
    catch (OperationInterrupt& e)
    {
        if (e.primed)
            std::cerr << "Error" << std::endl;
    }
}