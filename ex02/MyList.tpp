/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyList.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:38:26 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/10 12:11:55 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <class Container>
MyList<Container>::MyList()
{
    internal_list_size = 0;
    internal_list_head = NULL;
}

template <class Container>
MyList<Container>::~MyList()
{
    delete_internal_list();
}

template <class Container>
MyList<Container>::MyList(int argc, char **argv)
{
    internal_list_head = NULL;
    internal_list_head = new Node<Container>;
    internal_list_head->cont.resize(argc - 1);
    int cur_pos = 0;
    while (cur_pos <= argc - 2)
    {
        internal_list_head->cont[cur_pos] = _atoi(argv[cur_pos + 1]);
        cur_pos++;
    }
    internal_list_head->prev = NULL;
    internal_list_head->next = NULL;
    internal_list_head->idx = 0;
    internal_list_size = 1;
}

template <class Container>
void MyList<Container>::create_list_head(int argc, char **argv)
{
    internal_list_head = NULL;
    internal_list_head = new Node<Container>;
    internal_list_head->cont.resize(argc - 1);
    int cur_pos = 0;
    while (cur_pos <= argc - 2)
    {
        internal_list_head->cont[cur_pos] = _atoi(argv[cur_pos + 1]);
        cur_pos++;
    }
    internal_list_head->prev = NULL;
    internal_list_head->next = NULL;
    internal_list_head->idx = 0;
    internal_list_size = 1;
}

template <class Container>
void MyList<Container>::delete_internal_list()
{
    if (internal_list_head == NULL)
        return ;
    Node<Container> *cur = internal_list_head;
    Node<Container> *prev;
    while (cur)
    {
        prev = cur;
        cur = cur->next;
        delete prev;
    }
}

template <class Container>
Container& MyList<Container>::operator[](int index)
{
    Node<Container> *cur = internal_list_head;
    if (!cur)
        throw OperationInterrupt(UNPRIMED);
    int idx = 0;
    while (cur && idx != index)
    {
        cur = cur->next;
        idx++;
    }
    if (idx < index)
        throw OperationInterrupt(UNPRIMED);
    return (cur->cont);
}

template <class Container>
void MyList<Container>::setup_next_depth()
{
    int sm_size = get_smallest_cont_size();
    int next_cont_size = (sm_size / 2); //+ (sm_size % 2); //do i move the +1 or not?
    old_size = internal_list_size;
    while (internal_list_size < (old_size * 2))
    {
        attach_new_node(next_cont_size);
    }
}

template <class Container>
void MyList<Container>::eliminate_empty_nodes()
{
    Node<Container> *cur = internal_list_head;
    Node<Container> *prev;
    while (cur)
    {
        if (cur->cont.empty())
        {  
            prev = cur;
            cur = cur->next;
            delete prev;
        }
        else
            cur = cur->next;
    }
    size(); //updates list size and indexes
}

template <class Container>
void MyList<Container>::attach_new_node(int cont_size)
{
    Node<Container> *to_add = new Node<Container>;
    Node<Container> *cur = internal_list_head;
    while (cur && cur->next)
        cur = cur->next;
    cur->next = to_add;
    to_add->next = NULL;
    to_add->prev = cur;
    to_add->cont.resize(cont_size);
    to_add->idx = internal_list_size;
    internal_list_size++;
}

//updates internal__list_size variable. reindexes all nodes in the chain.
template <class Container>
int MyList<Container>::size()
{
    internal_list_size = 0;
    Node<Container> *cur = internal_list_head;
    if (cur == NULL)
        return (-1);
    while (cur)
    {
        cur->idx = internal_list_size;
        internal_list_size++;
        cur = cur->next;
    }
    return (internal_list_size);
}

template <class Container>
int MyList<Container>::get_smallest_cont_size()
{
    Node<Container> *cur = internal_list_head;
    if (cur == NULL)
        return (-1);
    while (cur && cur->next)
        cur = cur->next;
    return (cur->cont.size());
}