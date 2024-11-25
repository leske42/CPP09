/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:54:50 by mhuszar           #+#    #+#             */
/*   Updated: 2024/11/25 20:18:58 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMERGE_HPP
# define AMERGE_HPP

#include <iostream>
#include <algorithm>
#include <cmath>
#include "MyList.hpp"
#include "PairKeeper.hpp"

#define DUMMY_VAL 2147483650

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif

#ifndef COUNT
# define COUNT 0
#endif

#define MIL 1000000

template <class Container>
class AMerge
{

    public:

        AMerge(void);
        ~AMerge(void);

    private:

        AMerge(const AMerge& other);
        AMerge& operator=(const AMerge& other);

    protected:

        virtual void    do_sort(int argc, char **argv) = 0;

        void            take_apart();
        void            assemble();

        void            intake_sequence(int argc, char **seq);
        int             calculate_depth(int argc);

        int             my_pair(int my_num);
        int             my_pair_up(int my_num, int diff);
        void            create_sequence(Container& cont, Container& pair);
        void            follow_sequence(Container& cont, Container& pair);
        void            merge_containers(Container& from, Container& to);
        void            copy_merge(Container& from, Container& to);
        void            reassess_size();
        void            clear_dummy_vals(Container& cont);
        void            print_content(Container& cont);
        
        typename Container::iterator recalc_bounds(Container& from, int jacob_index);
        typename Container::iterator calc_last(Container& cont, int idx);
    
    
        int             depth;
        int             recursion_levels;
        int             bottom;
        int             breakpoint;

        int             prev_containers;
        int             cur_containers;
        int             seq_max;
        int             comp;
        int             og_size;

        typename Container::iterator        last_bound;
        Container                           sequence;
        Container                           infiniteJakob;
        MyList<Container>                   cont_chain;
        PairKeeper                          lookup;
        std::deque < std::pair < int, int > > inserted;
};

long int        ft_atoi(const char *str);

#include "AMerge.tpp"

#endif