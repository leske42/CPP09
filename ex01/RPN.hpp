/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:44:24 by mhuszar           #+#    #+#             */
/*   Updated: 2024/10/05 11:50:43 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <list>
#include <cstdlib>

#define INT_MAX 2147483647
#define MUL 2147483689
#define ADD 2147483690
#define SUB 2147483692
#define DIV 2147483694

class RPN
{
    public:

        RPN(void);
        RPN(std::string input);
        ~RPN(void);

    private:
        
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);

        bool ValidOperand(char& op);
        void ValidateLine(std::string& line);
        void FillStack(const char *input);
        void DoCalc(void);
        void _do_prologue();
        void _setup_vals_and_calc();
        void _execute_calc(long int first, long int second, long int operand);
        void _do_epilogue();

        std::list<long int> stack;
        std::list<long int> other_stack;
        
        long int inspect;

};

#endif