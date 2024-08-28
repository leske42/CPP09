/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:52:20 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/28 18:53:59 by mhuszar          ###   ########.fr       */
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
        ValidateLine(input);
    }
    catch (OperationInterrupt& e)
    {
        std::cerr << "Error" << std::endl;
    }
}