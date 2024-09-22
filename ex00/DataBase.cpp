/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataBase.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:23:59 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/22 13:53:03 by mhuszar          ###   ########.fr       */
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
        //std::cout << line << std::endl;
        if (data.eof() && line.empty())
            break ;
        else if (line.empty())
            throw ParseException(DATABASE, idx, INC_ENT); //TODO: make its own error
        CheckRawFormat(line, idx);
        ValidateLine(line, idx, DATABASE);
        line.clear();
        if (data.eof())
            break ;
        idx++;
    }
    //std::cout << "DataBase created & values stored" << std::endl;
    data.close();
}

void DataBase::SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val)
{
    //TODO: use strtod() or ft_atoi() here
    const char *str = line.c_str();

    //TODO: put try_catch block here
    year = ft_atoi(str);
    while (*str != '-')
        str++;
    str++;
    month = ft_atoi(str); //cannot jump with += 3 cause they can give OF atp
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
    std::map<uint32_t, float>::iterator iter;
    std::pair<uint32_t, float> unit;
    iter = BitcoinDB.lower_bound(val);
    unit = *iter;
    if (unit.first == val)
        return (unit.second);
    else if (iter == BitcoinDB.begin())
        throw OperationInterrupt(); //ParseException would be better
    iter--;
    unit = *iter;
    return (unit.second);
}