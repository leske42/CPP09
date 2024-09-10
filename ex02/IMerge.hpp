/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:54:50 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/08 21:05:30 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMERGE_HPP
# define IMERGE_HPP

#include <iostream>
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

        int             calculate_depth(int argc);
        void            intake_sequence(int argc, char **seq);
        virtual void    execute() = 0;
        int             my_pair(int my_num);
        void            create_sequence();
        void            mirror_sequence(int my_num);
        void            print_content(int my_num);
        void            reassess_size();

        void            do_sort();
        void            take_apart();
        void            assemble();

        int             recursion_levels;
        int             depth;
        int             bottom;
        int             breakpoint;
    
        int             cur_level; //called depth now
        int             max_containers;
        int             prev_containers;
        int             cur_containers;

        MyList<Container>   cont_chain;
        Container           sequence;
        //Container       *cont_chain;
};

long int	_atoi(const char *str);

#include "IMerge.tpp"

#endif