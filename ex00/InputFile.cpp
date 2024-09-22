/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputFile.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:24:06 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/22 11:55:51 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InputFile.hpp"
#include <map>

void InputFile::SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val)
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

void InputFile::CheckRawFormat(std::string& line, int idx)
{
    std::string::iterator iter = line.begin();
    for (int i = 0; i < 3; i++)
    {
        while (iter != line.end() && isdigit(*iter))
            iter++;
        if (i == 2 && (iter == line.end() || *iter != ' '))
            throw ParseException(INPUT, idx, *iter);
        else if (i < 2 && (iter == line.end() || *iter != '-'))
            throw ParseException(INPUT, idx, *iter);
        iter++;
    }
    if (iter == line.end() || *iter != '|')
        throw ParseException(INPUT, idx, *iter);
    iter++;
    if (iter == line.end() || *iter != ' ')
        throw ParseException(INPUT, idx, *iter);
    iter++;
    if (iter != line.end() && *iter == '-')
        iter++;
    if (iter == line.end())
        throw ParseException(INPUT, idx, INV_SEP);
    while (iter != line.end() && isdigit(*iter))
        iter++;
    if (iter != line.end() && *iter == '.')
        iter++;
    while (iter != line.end() && isdigit(*iter))
        iter++;
    if (iter != line.end())
        throw ParseException(INPUT, idx, *iter);
}

InputFile::InputFile(void)
{
    
}

InputFile::~InputFile(void)
{
    
}

void InputFile::ParseInput(char *target)
{
    std::ifstream data;
    std::string line;
    data.open(target);
    if (!data.is_open())
        throw ParseException(INPUT, 0, FILE_NOP);
    std::getline(data, line);
    if (data.eof())
        throw ParseException(INPUT, 0, EMPTY);
    else if (line != "date | value")
        throw ParseException(INPUT, 1, HEADER);
    int idx = 2;
    while (1)
    {
        std::getline(data, line);
        //std::cout << line << std::endl;
        if (line.empty() && data.eof())
            break ;
        else if (line.empty())
        {
            idx++;
            continue ;
        }
        try
        {
            CheckRawFormat(line, idx);
            ValidateLine(line, idx, INPUT);
        }
        catch (ParseException& e)
        {
            e.displayIssue();
        }
        line.clear();
        if (data.eof())
            break ;
        idx++;
    }
    //std::cout << "InputFile created & values stored" << std::endl;
    data.close();
}

std::pair<uint32_t, float> InputFile::get_next_val(void)
{
    if (BitcoinDB.empty())
        throw OperationInterrupt();
    std::pair<uint32_t, float> ret;
    std::map<uint32_t, float>::iterator iter = BitcoinDB.begin();
    ret = *iter;
    BitcoinDB.erase(iter);
    DisplayLog(ret);
    return (ret);
    //return (std::pair<uint32_t, float>(10, 10.0));
}

void InputFile::DisplayLog(std::pair<uint32_t, float> log)
{
    uint32_t rawBits = log.first;
    uint32_t year = rawBits >> 16;
    uint32_t mon = (rawBits >> 8) & 255;
    uint32_t day = rawBits & 255;
    
    std::cout << year << "-";
    if (mon < 10)
        std::cout << 0;
    std::cout << mon << "-";
    if (day < 10)
        std::cout << 0;
    std::cout << day << " => ";
    std::cout << log.second << " = ";
}