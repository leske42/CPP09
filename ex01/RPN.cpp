/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:44:22 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/29 19:08:03 by mhuszar          ###   ########.fr       */
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
            stack.push_front((long)*str + 2147483647);
        else if (*str != ' ')
            stack.push_front(atoi(str));
        str++;
    }
}

void RPN::_do_prologue()
{
    if (stack.empty())
        throw OperationInterrupt(PRIMED);
    first = stack.back();
    stack.pop_back();
    if (first > INT_MAX)
        throw OperationInterrupt(PRIMED);
    else if (stack.empty())
    {
        std::cout << first << std::endl;
        throw OperationInterrupt(UNPRIMED);
    }
    second = stack.back();
    stack.pop_back();
    if (stack.empty() || second > INT_MAX)
        throw OperationInterrupt(PRIMED);
    operand = stack.back();
    stack.pop_back();
    if (operand < INT_MAX)
    {
        std::cerr << operand << std::endl;
        throw OperationInterrupt(PRIMED);
    }
}

void RPN::_execute_calc()
{
    long int result;
    
    switch (operand)
    {
        case ADD:
            result = first + second;
            break;
        case SUB:
            result = first - second;
            break;
        case MUL:
            result = first * second;
            break;
        case DIV:
            result = first / second;
            break;
    }
    if (result > INT_MAX)
    {
        std::cerr << "Overflow ";
        throw (OperationInterrupt(PRIMED));
    }
    stack.push_back(result);
    first = second = result = 0;
}

void RPN::DoCalc()
{
    while (1)
    {
        _do_prologue();
        _execute_calc();
    }
}