/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:09 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/24 00:23:32 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EX_HPP
# define BITCOIN_EX_HPP

#include <iostream>
#include <exception>
#include <stdint.h>
#include <map>

enum Issue
{
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

#define DATABASE 0
#define INPUT 1

class BitcoinExchange
{
    public:

        BitcoinExchange(void);
        ~BitcoinExchange(void);
        
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

        void CreateDB();
    
    private:
    
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        
        void ValidateLine(std::string& line, int idx);
        void StoreLine(std::string& line);
        void SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val);
        void CheckRawFormat(std::string& line, int idx, int mode);
        // void StoreValue(uint32_t& val);

        std::map<uint32_t, float> BitcoinDB;
        
};

#endif