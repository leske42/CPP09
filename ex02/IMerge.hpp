/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:54:50 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/31 18:14:55 by mhuszar          ###   ########.fr       */
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
        void intake_sequence(int argc, char **seq);
        virtual void execute() = 0;
    
        Container cont;
};

long int	_atoi(const char *str);

#include "IMerge.tpp"

#endif