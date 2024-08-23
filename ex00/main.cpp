/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:12 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/24 00:12:08 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(void)
{
    BitcoinExchange DBHolder;
    
    try
    {
        DBHolder.CreateDB();
        //throw ParseException(DATABASE, 0, OTHER);
    }
    catch (BitcoinExchange::ParseException& e)
    {
        e.displayIssue();
    }
}