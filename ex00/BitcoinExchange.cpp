/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:07 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/25 20:56:04 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <cstdlib>

void BitcoinExchange::ParseException::displayIssue()
{
    if (location == DATABASE)
        std::cerr << "[corrupted database] ";
    else
        std::cerr << "[invalid input] ";
    if (issue != FILE_NOP && issue != EMPTY)
        std::cerr << "On line " << line << ": ";
    switch (issue)
    {
        case INC_ENT:
            std::cerr << "Incomplete entry";
            break;
        case FILE_NOP:
            std::cerr << "File could not be opened";
            break;
        case EMPTY:
            std::cerr << "File is empty";
            break;
        case INV_SEP:
            std::cerr << "invalid separation format";
            break;
        case INV_CHAR:
            std::cerr << "invalid character detected";
            break;
        case YEAR_RNG:
            std::cerr << "year should be between 2009 and 2024";
        case MON_RNG:
            std::cerr << "month out of range";
            break;
        case DAY_RNG:
            std::cerr << "day out of range";
            break;
        case REQ_RNG:
            std::cerr << "request out of range";
            break;
        case NEG_NUM:
            std::cerr << "negative request detected";
            break;
        default:
            std::cerr << "wrong input format";
    }
    std::cerr << std::endl;
}

BitcoinExchange::ParseException::ParseException(const ParseException& other)
{
    (void)other;
}

BitcoinExchange::ParseException::ParseException(int loc, unsigned int ln, int type)
{
    if (isprint(type))
    {
        if (type == '-' || type == '.' || type == ',' || type == ' ' || type == '|')
            issue = INV_SEP;
        else
            issue = INV_CHAR;
    }
    else
        issue = type;
    location = loc;
    line = ln;
}

BitcoinExchange::ParseException::~ParseException() throw() {}

void BitcoinExchange::SeparateValuesDB(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val)
{
    //TIP: use strtod() or ft_atoi() here
    const char *str = line.c_str();

    year = atoi(str);
    while (*str != '-')
        str++;
    str++;
    month = atoi(str); //cannot jump with += 3 cause they can give OF atp
    while (*str != '-')
        str++;
    str++;
    day = atoi(str);
    while (*str != ',')
        str++;
    str++;
    val = atof(str);
}

void BitcoinExchange::SeparateValuesIN(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val)
{
    //TIP: use strtod() or ft_atoi() here
    const char *str = line.c_str();

    year = atoi(str);
    while (*str != '-')
        str++;
    str++;
    month = atoi(str); //cannot jump with += 3 cause they can give OF atp
    while (*str != '-')
        str++;
    str++;
    day = atoi(str);
    while (*str != '|')
        str++;
    str += 2;
    val = atof(str);
}

void BitcoinExchange::ValidateLine(std::string& line, int idx, int mode)
{
    uint32_t year;
    uint32_t mon;
    uint32_t day;
    float val;

    uint32_t res;
    
    if (mode == DATABASE)
        SeparateValuesDB(line, year, mon, day, val);
    else
        SeparateValuesIN(line, year, mon, day, val);

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

    res = year << 16 | mon << 8 | day;

    if (mode == DATABASE)
        BitcoinDB.insert(std::pair<uint32_t, float>(res, val));
    else if (mode == INPUT)
        RequestDB.insert(std::pair<uint32_t, float>(res, val));
}

void BitcoinExchange::CheckRawFormatDB(std::string& line, int idx)
{
    std::string::iterator iter = line.begin();
    for (int i = 0; i < 5; i++)
    {
        while (iter != line.end() && isdigit(*iter))
            iter++;
        if (i >= 3 && iter == line.end())
            break ;
        else if ((i == 3 && *iter != '.') || i == 4)
            throw ParseException(DATABASE, idx, *iter);
        else if (i == 2 && (iter == line.end() || *iter != ','))
            throw ParseException(DATABASE, idx, *iter);
        else if (i < 2 && (iter == line.end() || *iter != '-'))
            throw ParseException(DATABASE, idx, *iter);
        iter++;
        if (i == 3 && iter == line.end())
            throw ParseException(DATABASE, idx, *iter);
    }
}

void BitcoinExchange::CheckRawFormatIN(std::string& line, int idx)
{
    std::string::iterator iter = line.begin();
    for (int i = 0; i < 3; i++)
    {
        while (iter != line.end() && isdigit(*iter))
            iter++;
        if (i == 2 && (iter == line.end() || *iter != ' '))
            throw ParseException(DATABASE, idx, *iter);
        else if (i < 2 && (iter == line.end() || *iter != '-'))
            throw ParseException(DATABASE, idx, *iter);
        iter++;
    }
    if (iter == line.end() || *iter != '|')
        throw ParseException(DATABASE, idx, *iter);
    iter++;
    if (iter == line.end() || *iter != ' ')
        throw ParseException(DATABASE, idx, *iter);
    iter++;
    if (iter != line.end() && *iter == '-')
        iter++;
    if (iter == line.end())
        throw ParseException(DATABASE, idx, INV_SEP);
    while (iter != line.end() && isdigit(*iter))
        iter++;
    if (iter != line.end())
        throw ParseException(DATABASE, idx, *iter);
}
//if line end then all of the stars will cry cause of deref....
//actually not cause of the NULL but still standard dont like it

void BitcoinExchange::CreateDB()
{
    std::ifstream data;
    std::string line;
    data.open("data.csv");
    if (!data.is_open())
        throw ParseException(DATABASE, 0, FILE_NOP);
    std::getline(data, line);
    if (line.empty())
        throw ParseException(DATABASE, 0, EMPTY);
    int idx = 2;
    while (1)
    {
        std::getline(data, line);
        //std::cout << line << std::endl;
        if (line.empty())
            break ;
        CheckRawFormatDB(line, idx);
        ValidateLine(line, idx, DATABASE);
        line.clear();
        if (data.eof())
            break ;
        idx++;
    }
    std::cout << "DataBase created & values stored" << std::endl;
    data.close();
}

BitcoinExchange::BitcoinExchange()
{
    
}

BitcoinExchange::~BitcoinExchange()
{
    
}
