/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:07 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/23 21:09:16 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>

void ParseException::displayIssue()
{
    if (location == DATABASE)
        std::cerr << "[corrupted database] ";
    else
        std::cerr << "[invalid input] ";
    if (issue != FILE_NOP)
        std::cerr << "On line " << line << ": ";
    switch (issue)
    {
        case FILE_NOP:
            std::cerr << "File could not be opened";
            break;
        case INV_SEP:
            std::cerr << "invalid separation format";
            break;
        case INV_CHAR:
            std::cerr << "non-numeric character detected";
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

ParseException::ParseException(const ParseException& other) {
    (void)other;
}

ParseException::ParseException(int loc, unsigned int ln, int type) {
    location = loc;
    line = ln;
    issue = type;
}

ParseException::~ParseException() throw() {}

void ValidateLine(std::string& line)
{
    (void)line;
}

void StoreLine(std::string& line) //actually can be a ref cause i will store an int anyway
{
    (void)line;
}

void CreateDB()
{
    std::ifstream data;
    std::string line;
    data.open("data.csv");
    if (!data.is_open())
        throw ParseException(DATABASE, 0, FILE_NOP);
    while (1)
    {
        std::getline(data, line);
        if (line.empty())
            break ;
        ValidateLine(line);
        StoreLine(line);
        line.clear();
        if (data.eof())
            break ;
    }
    std::cout << "DataBase created & values stored" << std::endl;
}
