/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputFile.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:24:09 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/27 14:12:42 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTFILE_HPP
# define INPUTFILE_HPP

#include "BitcoinExchange.hpp"
#include "ParseException.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>

class InputFile : public BitcoinExchange
{
    public:

        InputFile(void);
        ~InputFile(void);

        void ParseInput(void);
        std::pair<uint32_t, float> get_next_val(void); //for now without &

    private:

        InputFile(const InputFile& other);
        InputFile& operator=(const InputFile& other);

        void CheckRawFormat(std::string& line, int idx);
        void SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val);
};

#endif