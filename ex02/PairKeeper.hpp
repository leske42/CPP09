/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PairKeeper.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:35:34 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/16 12:30:52 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIRKEEPER_HPP
# define PAIRKEEPER_HPP

#include <deque>

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

        std::deque<int> indexes;
        int max;
};

#endif