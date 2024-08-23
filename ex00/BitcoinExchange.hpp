/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:09 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/23 20:32:24 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EX_HPP
# define BITCOIN_EX_HPP

#include <iostream>
#include <exception>

enum Issue
{
    INV_SEP,
    INV_CHAR,
    MON_RNG,
    DAY_RNG,
    REQ_RNG,
    NEG_NUM,
    FILE_NOP,
    OTHER
};

#define DATABASE 0
#define INPUT 1

class ParseException : public std::exception
{
    public:

        ParseException(int loc, unsigned int ln, int type);
        ~ParseException() throw();
        ParseException(const ParseException& other);
    
        void displayIssue();

    private:

        ParseException(void);
        ParseException& operator=(const ParseException& other);
        unsigned int line;
        int location;
        int issue;
};

void ValidateLine(std::string& line);
void StoreLine(std::string& line);
void CreateDB();

#endif