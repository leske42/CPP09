/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:44:22 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/28 18:54:19 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "OperationInterrupt.hpp"

bool ValidOperand(char& op)
{
    if (op == '+' || op == '-' || op == '/' || op == '*')
        return (true);
    else
        return (false);
}

void ValidateLine(std::string& line)
{
    std::string::iterator iter = line.begin();
    while (iter != line.end())
    {
        if (!isdigit(*iter) && !ValidOperand(*iter))
            throw OperationInterrupt();
        iter++;
        if (iter == line.end())
            break ;
        if (*iter != ' ')
            throw OperationInterrupt();
        iter++;
    }
}