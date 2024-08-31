/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:54:50 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/31 19:19:52 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMERGE_HPP
# define IMERGE_HPP

#include <iostream>

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

        void calculate_depth(int argc);
        void intake_sequence(int argc, char **seq);
        virtual void execute() = 0;

        int recursion_levels;
        int cur_level;
        int max_containers;
        int cur_containers;
        Container cont;
        Container *cont_chain;
};

long int	_atoi(const char *str);

#include "IMerge.tpp"

#endif