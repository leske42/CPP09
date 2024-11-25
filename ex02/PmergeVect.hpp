/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeVect.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:29:11 by mhuszar           #+#    #+#             */
/*   Updated: 2024/11/25 20:18:58 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_VECT_HPP
# define PMERGE_VECT_HPP

#include "AMerge.hpp"
#include <iostream>
#include <vector>

class PmergeVect : public AMerge< std::vector<long int> >
{
    public:

        PmergeVect(void);
        ~PmergeVect(void);
        PmergeVect(int argc, char **argv);
    
    private:

        PmergeVect(const PmergeVect& other);
        PmergeVect& operator=(const PmergeVect& other);

        void    do_sort(int argc, char **argv);

};

#endif