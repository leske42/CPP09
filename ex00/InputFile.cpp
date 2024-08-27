/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputFile.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:24:06 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/27 14:12:39 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InputFile.hpp"

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

InputFile::InputFile(void)
{
    
}

InputFile::~InputFile(void)
{
    
}

void InputFile::ParseInput(void)
{
    
}

std::pair<uint32_t, float> InputFile::get_next_val(void)
{
    return (std::pair<uint32_t, float>(10, 10.0));
}