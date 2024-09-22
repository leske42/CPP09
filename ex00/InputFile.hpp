/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputFile.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:24:09 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/22 14:14:34 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTFILE_HPP
# define INPUTFILE_HPP

#include "BitcoinExchange.hpp"
#include "ParseException.hpp"
#include "OperationInterrupt.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>

class InputFile : public BitcoinExchange
{
    public:

        InputFile(void);
        ~InputFile(void);

        void ParseInput(char *target);

    private:

        InputFile(const InputFile& other);
        InputFile& operator=(const InputFile& other);

        void CheckRawFormat(std::string& line, int idx);
        void SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val);
        void DisplayLog(std::pair<uint32_t, float> log);
};

#endif