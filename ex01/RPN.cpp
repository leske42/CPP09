/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:44:22 by mhuszar           #+#    #+#             */
/*   Updated: 2024/10/05 11:46:03 by mhuszar          ###   ########.fr       */
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
    int digit_ctr = 0;
    int op_ctr = 0;
    char *str = const_cast<char *>(input);

    while (*str)
    {
        if (ValidOperand(*str))
        {
            stack.push_front((long)*str + 2147483647);
            op_ctr++;
        }
        else if (*str != ' ')
        {
            stack.push_front(atoi(str));
            digit_ctr++;
        }
        if (digit_ctr >= 2 && op_ctr > (digit_ctr - 1))
            throw OperationInterrupt(PRIMED);
        str++;
    }
    if (op_ctr != (digit_ctr - 1))
        throw OperationInterrupt(PRIMED);
}

void RPN::_do_prologue()
{
    if (stack.empty())
        throw OperationInterrupt(PRIMED);
    inspect = stack.back();
    stack.pop_back();
    if (inspect > INT_MAX)
        throw OperationInterrupt(PRIMED);
    else if (stack.empty())
    {
        std::cout << inspect << std::endl;
        throw OperationInterrupt(UNPRIMED);
    }
    other_stack.push_back(inspect);
    inspect = stack.back();
    stack.pop_back();
    if (stack.empty() || inspect > INT_MAX)
        throw OperationInterrupt(PRIMED);
    while (inspect < INT_MAX)
    {
        other_stack.push_back(inspect);
        inspect = stack.back();
        stack.pop_back();
    }
}

void RPN::_setup_vals_and_calc()
{
    long int second = other_stack.back();
    other_stack.pop_back();
    long int first = other_stack.back();
    other_stack.pop_back();
    _execute_calc(first, second, inspect);
    inspect = 0;
}

void RPN::_do_epilogue()
{
    long int temp;

    while (!other_stack.empty())
    {
        temp = other_stack.back();
        other_stack.pop_back();
        stack.push_back(temp);
    }
}

void RPN::_execute_calc(long int first, long int second, long int operand)
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
        {
            if (second == 0)
                throw (OperationInterrupt(PRIMED));
            result = first / second;
            break;
        }
    }
    if (result > INT_MAX)
    {
        std::cerr << "Overflow ";
        throw (OperationInterrupt(PRIMED));
    }
    stack.push_back(result);
}

void RPN::DoCalc()
{
    while (1)
    {
        _do_prologue();
        _setup_vals_and_calc();
        _do_epilogue();
    }
}
