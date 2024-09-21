/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:09 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/21 22:21:59 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EX_HPP
# define BITCOIN_EX_HPP

#include <iostream>
#include <exception>
#include <stdint.h>
#include <map>

#define DATABASE 0
#define INPUT 1

class BitcoinExchange
{
    public:

        BitcoinExchange(void);
        ~BitcoinExchange(void);

        void link_other(BitcoinExchange *other);

    private:

        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
    
    protected:
        
        virtual void    CheckRawFormat(std::string& line, int idx) = 0;
        virtual float   LookupVal(uint32_t val);
        virtual void    SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val);
        void            ValidateLine(std::string& line, int idx, int mode);
        void            displayResult(std::string& line, float result);

        std::map<uint32_t, float>   BitcoinDB;
        BitcoinExchange             *other_link;
};

//void StoreLine(std::string& line);
// void SeparateValuesDB(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val);
// void SeparateValuesIN(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val);
// void CheckRawFormatDB(std::string& line, int idx);
// void CheckRawFormatIN(std::string& line, int idx);
// void StoreValue(uint32_t& val);

#endif