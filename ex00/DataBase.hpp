/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataBase.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:24:01 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/27 17:17:37 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATABASE_HPP
# define DATABASE_HPP

#include "BitcoinExchange.hpp"
#include "ParseException.hpp"
#include "OperationInterrupt.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>

class DataBase : public BitcoinExchange
{
    public:

        DataBase(void);
        ~DataBase(void);

        void CreateDB(void);
        float LookupVal(uint32_t val);

    private:

        DataBase(const DataBase& other);
        DataBase& operator=(const DataBase& other);

        void CheckRawFormat(std::string& line, int idx);
        void SeparateValues(std::string& line, uint32_t& year, uint32_t& month, uint32_t& day, float& val);
};

#endif