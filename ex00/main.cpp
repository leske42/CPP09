/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:12 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/27 15:00:16 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "DataBase.hpp"
#include "InputFile.hpp"
#include "ParseException.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Need exactly one argument [inputfile]" << std::endl;
        return (0);
    }
    
    DataBase DBHolder;
    InputFile InputHolder;
    
    try
    {
        InputHolder.ParseInput(argv[1]);
        DBHolder.CreateDB();
        //throw ParseException(DATABASE, 0, OTHER);
    }
    catch (ParseException& e)
    {
        e.displayIssue();
    }
    catch (OperationInterrupt& e)
    {
        return (0);
    }
}