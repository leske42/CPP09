/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:10 by mhuszar           #+#    #+#             */
/*   Updated: 2024/11/25 20:18:58 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_HPP
# define PMERGE_HPP

#include "AMerge.hpp"
#include <iostream>
#include <deque>

class PmergeMe : public AMerge< std::deque<long int> >
{
    public:

        PmergeMe(void);
        ~PmergeMe(void);
        PmergeMe(int argc, char **argv);
    
    private:

        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);

        void    do_sort(int argc, char **argv);

};

#endif