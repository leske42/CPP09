/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PairKeeper.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:35:34 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/17 14:04:07 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIRKEEPER_HPP
# define PAIRKEEPER_HPP

#include <deque>

#define DUMMY_VAL 2147483650

class PairKeeper
{
    public:

        PairKeeper(void);
        ~PairKeeper(void);

        void    initialize(int size);
        //usage will be: iter = cont.begin() + pairIndex(cur - cont.begin())
        int     pairIndex(int idx);
        void    adjustPositions(int inserted_at);
    
    private:

        PairKeeper(const PairKeeper& other);
        PairKeeper& operator=(const PairKeeper& other);

        std::deque<long int> indexes;
        std::deque<long int> dummy_cont;
        int max;
        int dummy_max;
};

#endif