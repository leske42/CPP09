/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:10 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/08 21:04:01 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_HPP
# define PMERGE_HPP

#include "IMerge.hpp"
#include <iostream>
#include <deque>

class PmergeMe : public IMerge< std::deque<int> >
{
    public:

        PmergeMe(void);
        ~PmergeMe(void);
        PmergeMe(int argc, char **argv);
    
    private:

        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);

        // void calculate_depth();
        void execute();
        
        //int depth;
        
        //std::deque<int> cont;
};

#endif