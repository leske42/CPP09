/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:54:50 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/10 16:38:11 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMERGE_HPP
# define IMERGE_HPP

#include <iostream>
#include <algorithm> 
#include "MyList.hpp"

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

        virtual void    do_sort(int argc, char **argv) = 0;

        void            take_apart();
        void            assemble();

        void            intake_sequence(int argc, char **seq);
        int             calculate_depth(int argc);

        int             my_pair(int my_num);
        void            create_sequence();
        void            mirror_sequence(int my_num);
        void            merge_containers(Container& from, Container& to);
        void            reassess_size();

        void            print_content(int my_num);
    
        int             depth;
        int             recursion_levels;
        int             bottom;
        int             breakpoint;

        int             prev_containers;
        int             cur_containers;

        MyList<Container>   cont_chain;
        Container           sequence;
};

long int        ft_atoi(const char *str);

#include "IMerge.tpp"

#endif