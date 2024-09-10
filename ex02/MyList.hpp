/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyList.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:28:09 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/10 12:28:23 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYLIST_HPP
# define MYLIST_HPP

#include <iostream>
#include "OperationInterrupt.hpp"

long int	_atoi(const char *str);

template <class Container>
struct Node
{
    Container cont;
    struct Node *next;
    struct Node *prev;
    int idx;
};

template <class Container>
class MyList
{
    public:
        
        MyList(void);
        MyList(int argc, char **argv);
        ~MyList(void);

        Container&  operator[](int index);
        void        create_list_head(int argc, char **argv);
        void        setup_next_depth();
        void        eliminate_empty_nodes();
        int         size();
        void        display_list();

        int         old_size;
        
    private:

        MyList(const MyList& other);
        MyList& operator=(const MyList& other);

        void    attach_new_node(int cont_size);
        int     get_smallest_cont_size();
        void    delete_internal_list();

        int             internal_list_size;
        Node<Container> *internal_list_head;
};

#include "MyList.tpp"

#endif