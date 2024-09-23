/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataBase.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:23:59 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/22 14:44:01 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DataBase.hpp"

void DataBase::CreateDB()
{
    std::ifstream data;
    std::string line;
    data.open("data.csv");
    if (!data.is_open())
        throw ParseException(DATABASE, 0, FILE_NOP);
    std::getline(data, line);
    if (data.eof())
        throw ParseException(DATABASE, 0, EMPTY);
    else if (line != "date,exchange_rate")
        throw ParseException(DATABASE, 1, HEADER);
    int idx = 2;
    while (1)
    {
        std::getline(data, line);
        if (data.eof() && line.empty())
            break ;
        else if (line.empty())
            throw ParseException(DATABASE, idx, INC_ENT);
        CheckRawFormat(line, idx);
        ValidateLine(line, idx, DATABASE);
        line.clear();
        if (data.eof())
            break ;
        idx++;
    }
    data.close();
}

void DataBase::SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val)
{
    const char *str = line.c_str();

    year = ft_atoi(str);
    while (*str != '-')
        str++;
    str++;
    month = ft_atoi(str);
    while (*str != '-')
        str++;
    str++;
    day = ft_atoi(str);
    while (*str != ',')
        str++;
    str++;
    val = atof(str);
}

void DataBase::CheckRawFormat(std::string& line, int idx)
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

DataBase::DataBase(void)
{
    
}

DataBase::~DataBase(void)
{
    
}

float DataBase::LookupVal(uint32_t val)
{
    bool of_flag = false;
    std::map<uint32_t, float>::iterator iter;
    std::pair<uint32_t, float> unit;

    iter = BitcoinDB.lower_bound(val);
    if (iter == BitcoinDB.end())
    {
        of_flag = true;
        iter--;
    }
    unit = *iter;
    if (unit.first == val || of_flag)
        return (unit.second);
    if (iter != BitcoinDB.begin())
        iter--;
    unit = *iter;
    return (unit.second);
}