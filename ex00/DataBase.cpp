/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataBase.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:23:59 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/27 14:12:48 by mhuszar          ###   ########.fr       */
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
        ValidateLine(line, idx, DATABASE);
        line.clear();
        if (data.eof())
            break ;
        idx++;
    }
    std::cout << "DataBase created & values stored" << std::endl;
    data.close();
}

void DataBase::SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val)
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
    (void) val;
    return (1.0);
}