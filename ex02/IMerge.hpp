/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:54:50 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/30 21:07:26 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMERGE_HPP
# define IMERGE_HPP

template <class Container>
class IMerge
{

    public:

        IMerge(void);
        ~IMerge(void);
        
    private:

        IMerge(const IMerge& other);
        IMerge& operator=(const IMerge& other);

    protected:

        //void calculate_depth();
    
        Container cont;
};

#include "IMerge.tpp"

#endif