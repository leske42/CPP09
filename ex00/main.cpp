/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:12 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/27 14:05:56 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "DataBase.hpp"
#include "InputFile.hpp"
#include "ParseException.hpp"

int main(void)
{
    DataBase DBHolder;
    InputFile InputHolder;
    
    try
    {
        DBHolder.CreateDB();
        //throw ParseException(DATABASE, 0, OTHER);
    }
    catch (ParseException& e)
    {
        e.displayIssue();
    }
}