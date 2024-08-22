/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:07 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/22 22:52:06 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void ParseException::DisplayIssue()
{
    if (location == DATABASE)
        std::cerr << "[corrupted database] ";
    else
        std::cerr << "[invalid input] ";
    std::cerr << "On line " << line << ": ";
    switch (issue)
    {
        case INV_SEP:
            std::cerr << "invalid separation format";
        case INV_CHAR:
            std::cerr << "non-numeric character detected";
        case MON_RNG:
            std::cerr << "month out of range";
        case DAY_RNG:
            std::cerr << "day out of range";
        case RQ_RNG:
            std::cerr << "request out of range";
        case NEG_NUM:
            std::cerr << "negative request detected";
        case OTHER:
            std::cerr << "wrong input format";
    }
    std::cerr << std::endl;
}

void ValidateLine(std::string& line)
{
    
}