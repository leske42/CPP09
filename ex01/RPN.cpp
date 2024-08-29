/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:44:22 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/29 18:40:38 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "OperationInterrupt.hpp"

bool RPN::ValidOperand(char& op)
{
    if (op == '+' || op == '-' || op == '/' || op == '*')
        return (true);
    else
        return (false);
}

void RPN::ValidateLine(std::string& line)
{
    std::string::iterator iter = line.begin();
    if (iter == line.end())
        throw OperationInterrupt(PRIMED);
    while (iter != line.end())
    {
        if (!isdigit(*iter) && !ValidOperand(*iter))
            throw OperationInterrupt(PRIMED);
        iter++;
        if (iter == line.end())
            break ;
        if (*iter != ' ')
            throw OperationInterrupt(PRIMED);
        iter++;
    }
}

RPN::RPN()
{
    //nothing
}

RPN::RPN(std::string input)
{
    ValidateLine(input);
    FillStack(input.c_str());
    DoCalc();
}

RPN::~RPN()
{
    
}

void RPN::FillStack(const char *input)
{
    char *str = const_cast<char *>(input);
    while (*str)
    {
        if (ValidOperand(*str))
            stack.push_back(*str + 2147483647);
        else if (*str != ' ')
            stack.push_back(atoi(str));
        str++;
    }
}

void RPN::_do_prologue()
{
    if (stack.empty())
        throw OperationInterrupt(PRIMED);
    first = stack.back();
    stack.pop_back();
    if (stack.empty())
    {
        std::cout << first << std::endl;
        throw OperationInterrupt(UNPRIMED);
    }
}

void RPN::DoCalc()
{
    _do_prologue();
}