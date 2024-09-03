/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:54:50 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/03 13:26:15 by mhuszar          ###   ########.fr       */
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

        void            calculate_depth(int argc);
        void            intake_sequence(int argc, char **seq);
        virtual void    execute() = 0;
        int             my_pair(int my_num);
        void            create_sequence();
        void            mirror_sequence(int my_num);

        int             recursion_levels;
        int             cur_level;
        int             max_containers;
        int             prev_containers;
        int             cur_containers;

        Container       *cont_chain;
        Container       sequence;
};

long int	_atoi(const char *str);

#include "IMerge.tpp"

#endif