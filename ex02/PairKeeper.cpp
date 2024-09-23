/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PairKeeper.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:35:36 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/21 18:10:15 by mhuszar          ###   ########.fr       */
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
    if (inserted_at > dummy_max)
    {
        if (DEBUG_MODE)
        {
            std::cerr << "wanted idx: " << inserted_at << " but max is: " << dummy_max;
            std::cerr << ". Returning from lookup... " << std::endl;
        }
        return ;
    }
    else
        dummy_max++;
    std::deque<long int>::iterator iter = dummy_cont.begin();
    iter = dummy_cont.begin();
    while (iternums < inserted_at)
    {
        if (*iter != DUMMY_VAL)
            actual_idx++;
        iternums++;
        iter++;
    }
    dummy_cont.insert(iter, DUMMY_VAL);
    iter = dummy_cont.begin() + iternums;
    while (iter != dummy_cont.end())
    {
        if (*iter < DUMMY_VAL)
            (*iter)++;
        iter++;
    }
    while (actual_idx <= max)
    {
        indexes[actual_idx]++;
        actual_idx++;
    }
}

void PairKeeper::print_content(char flag)
{
    std::deque<long int>::iterator cur; 
    if (flag == 'D')
    {
        cur = dummy_cont.begin();
        while (cur != dummy_cont.end())
        {
            std::cout << *cur << " ";
            if (*cur < 10)
                std::cout << " ";
            cur++;
        }
    }
    else
    {
        cur = indexes.begin();
        while (cur != indexes.end())
        {
            std::cout << *cur << " ";
            if (*cur < 10)
                std::cout << " ";
            cur++;
        }
    }
    std::cout << std::endl;
}
