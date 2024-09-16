/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PairKeeper.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:35:36 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/16 12:30:12 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PairKeeper.hpp"
#include "OperationInterrupt.hpp"

PairKeeper::PairKeeper(void)
{
    
}
PairKeeper::~PairKeeper(void)
{
    
}

void    PairKeeper::initialize(int size)
{
    int pos = 0;
    
    indexes.clear();
    indexes.resize(size);
    while (pos < size)
    {
        indexes[pos] = pos;
        pos++;
    }
    max = size - 1;
}
int     PairKeeper::pairIndex(int idx)
{
    if (idx > max)
        throw OperationInterrupt(PRIMED);
    return (indexes[idx]);
}

void    PairKeeper::adjustPositions(int inserted_at)
{
    if (inserted_at > max)
        throw OperationInterrupt(PRIMED);
    while (inserted_at <= max)
    {
        indexes[inserted_at]++;
        inserted_at++;
    }
}
