/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:09 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/27 14:12:10 by mhuszar          ###   ########.fr       */
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

    private:

        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
    
    protected:
        
        virtual void CheckRawFormat(std::string& line, int idx) = 0;
        void ValidateLine(std::string& line, int idx, int mode);
        virtual void SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val);

        std::map<uint32_t, float> BitcoinDB;
};

//void StoreLine(std::string& line);
// void SeparateValuesDB(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val);
// void SeparateValuesIN(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val);
// void CheckRawFormatDB(std::string& line, int idx);
// void CheckRawFormatIN(std::string& line, int idx);
// void StoreValue(uint32_t& val);

#endif