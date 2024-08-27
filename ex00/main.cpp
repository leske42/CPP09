/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:30:12 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/27 19:12:16 by mhuszar          ###   ########.fr       */
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
    
    InputFile   InputHolder;
    DataBase    DBHolder;
    
    try
    {
        InputHolder.ParseInput(argv[1]); //could turn these into constructors?
        DBHolder.CreateDB();

        while (1)
        {
            std::pair<uint32_t, float> cur_log = InputHolder.get_next_val();
            float result = DBHolder.LookupVal(cur_log.first) * cur_log.second;
            std::cout << result << std::endl;
        }
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