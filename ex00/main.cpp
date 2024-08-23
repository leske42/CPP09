/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:12 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/23 22:03:45 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(void)
{
    try
    {
        CreateDB();
        //throw ParseException(DATABASE, 0, OTHER);
    }
    catch (ParseException& e)
    {
        e.displayIssue();
    }
}