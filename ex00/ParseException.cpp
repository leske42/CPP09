/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseException.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:32:49 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/21 22:27:52 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseException.hpp"
#include "BitcoinExchange.hpp"

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
        case INC_ENT:
            std::cerr << "incomplete entry";
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

ParseException::~ParseException() throw() {}