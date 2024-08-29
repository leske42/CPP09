/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:44:24 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/29 13:27:36 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <deque>
#include <cstdlib>

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

        std::deque<long int> stack;
        
};

// void ValidateLine(std::string& line);

#endif