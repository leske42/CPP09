/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PairKeeper.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:35:36 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/17 14:08:03 by mhuszar          ###   ########.fr       */
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
    dummy_cont.resize(size);
    while (pos < size)
    {
        indexes[pos] = pos;
        dummy_cont[pos] = pos;
        pos++;
    }
    // dummy_cont = indexes;
    max = dummy_max = size - 1;
}
int     PairKeeper::pairIndex(int idx)
{
    if (idx > max)
        throw OperationInterrupt(PRIMED);
    return (indexes[idx]);
}

void    PairKeeper::adjustPositions(int inserted_at)
{
    int actual_idx = 0;
    int iternums = 0;
    if (inserted_at > dummy_max) //TODO: or .size() if also works
    {
        std::cout << "wanted idx: " << inserted_at << " but max is: " << max;
        std::cout << ". Returning from lookup... " << std::endl;
        return ;
    }
    else
        dummy_max++;
    std::deque<long int>::iterator iter = dummy_cont.begin();
    while (iternums < inserted_at)
    {
        if (*iter != DUMMY_VAL)
            actual_idx++;
        iternums++;
        iter++;
    }
    dummy_cont.insert(iter, DUMMY_VAL);
    while (actual_idx <= max)
    {
        // std::cout << "Incrementing " << indexes[actual_idx] << " to " << indexes[actual_idx] + 1 << std::endl;
        indexes[actual_idx]++;
        actual_idx++;
    }
}
