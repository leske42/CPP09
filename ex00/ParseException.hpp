/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseException.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:32:03 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/22 11:58:04 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_EXCEPTION_HPP
# define PARSE_EXCEPTION_HPP

#include <iostream>

enum Issue
{
    INC_ENT,
    HEADER,
    INV_SEP,
    INV_CHAR,
    YEAR_RNG,
    MON_RNG,
    DAY_RNG,
    REQ_RNG,
    NEG_NUM,
    FILE_NOP,
    EMPTY,
    OTHER
};

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

#endif