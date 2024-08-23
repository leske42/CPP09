/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:07 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/23 22:23:45 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <cstdlib>

void ParseException::displayIssue()
{
    if (location == DATABASE)
        std::cerr << "[corrupted database] ";
    else
        std::cerr << "[invalid input] ";
    if (issue != FILE_NOP && issue != EMPTY)
        std::cerr << "On line " << line << ": ";
    switch (issue)
    {
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

ParseException::ParseException(const ParseException& other)
{
    (void)other;
}

ParseException::ParseException(int loc, unsigned int ln, int type)
{
    if (isprint(type))
    {
        if (type == '-' || type == '.' || type == ',')
            issue = INV_SEP;
        else
            issue = INV_CHAR;
    }
    else
        issue = type;
    location = loc;
    line = ln;
}

ParseException::~ParseException() throw() {}

void ValidateLine(std::string& line)
{
    (void)line;
}

void CheckRawFormat(std::string& line, int idx)
{
    // uint32_t year;
    // uint32_t month;
    // uint32_t day;
    // uint32_t res;
    // std::string elem;

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
    }
}

void StoreLine(std::string& line) //actually can be a ref cause i will store an int anyway
{
    (void)line;
}

void CreateDB()
{
    // std::cout << "CDB called" << std::endl;
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
        CheckRawFormat(line, idx);
        //ValidateLine(line);
        //StoreLine(line);
        line.clear();
        if (data.eof())
            break ;
        idx++;
    }
    std::cout << "DataBase created & values stored" << std::endl;
    data.close();
}
