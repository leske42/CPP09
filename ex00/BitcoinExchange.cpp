/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:07 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/27 15:11:09 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "ParseException.hpp"
#include <fstream>
#include <cstdlib>

void BitcoinExchange::ValidateLine(std::string& line, int idx, int mode)
{
    uint32_t    year;
    uint32_t    mon;
    uint32_t    day;
    float       val;
    uint32_t    res;

    SeparateValues(line, year, mon, day, val);

    if (year < 2009 || year > 2024)
        throw ParseException(mode, idx, YEAR_RNG);
    if (mon < 1 || mon > 12)
        throw ParseException(mode, idx, MON_RNG);
    if (day < 1 || day > 31)
        throw ParseException(mode, idx, DAY_RNG);
    if (mon == 2 && (year == 2012 || year == 2016 || year == 2020
        || year == 2024) && day > 29)
        throw ParseException(mode, idx, DAY_RNG);
    else if (mon == 2 && day > 28)
        throw ParseException(mode, idx, DAY_RNG);
    if ((mon == 4 || mon == 6 || mon == 9 || mon == 11) && day > 30)
        throw ParseException(mode, idx, DAY_RNG);
    if (val < 0)
        throw ParseException(mode, idx, NEG_NUM);
    if (mode == INPUT && val > 1000)
        throw ParseException(mode, idx, REQ_RNG);

    res = year << 16 | mon << 8 | day;

    BitcoinDB.insert(std::pair<uint32_t, float>(res, val));
}

void BitcoinExchange::SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val)
{
    (void) line;
    (void) year;
    (void) month;
    (void) day;
    (void) val;
}

BitcoinExchange::BitcoinExchange()
{
    
}

BitcoinExchange::~BitcoinExchange()
{
    
}
