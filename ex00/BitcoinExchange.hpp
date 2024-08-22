/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:09 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/22 22:50:33 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EX_HPP
# define BITCOIN_EX_HPP

enum Issue
{
    INV_SEP,
    INV_CHAR,
    MON_RNG,
    DAY_RNG,
    REQ_RNG,
    NEG_NUM,
    
    OTHER
};

#define DATABASE 0
#define INPUT 1

class ParseException : public std::exception
{
    public:

        ParseException(int loc, unsigned int ln, int type);
        ~ParseException();
    
        void displayIssue();

    private:

        ParseException(void);
        ParseException(const ParseException& other);
        ParseException& operator=(const ParseException& other);
        unsigned int line;
        int location;
        int issue;
};

#endif