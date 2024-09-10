/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:52:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/08 21:09:55 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <class Container>
IMerge<Container>::IMerge(void)
{
    //cont_chain = NULL;
}

template <class Container>
IMerge<Container>::~IMerge(void)
{
    
}

/*
template <class Container>
void IMerge<Container>::intake_sequence(int argc, char ***seq)
{
    cont_chain[0].resize(argc - 1);
    int cur_pos = 0;
    while (cur_pos <= argc - 2)
    {
        //std::cout << "iter 1" << std::endl;
        cont_chain[0][cur_pos] = _atoi((*seq)[cur_pos + 1]);
        cur_pos++;
    }
    //std::cout << "size: " << cont_chain[0].size() << std::endl;
}*/

template <class Container>
void IMerge<Container>::intake_sequence(int argc, char **seq)
{
    cont_chain = MyList<Container>(argc, seq);
}

template <class Container>
int IMerge<Container>::calculate_depth(int argc)
{
    recursion_levels = 0;
    while (argc > 1)
    {
        argc /= 2;
        recursion_levels++;
    }
    max_containers = recursion_levels * 2;
    cur_containers = 2;
    prev_containers = 1;

    depth = 0;
    return (recursion_levels);
    //cur_level = 1;
}

template <class Container>
int IMerge<Container>::my_pair(int my_num)
{
    if (prev_containers + my_num > cur_containers)
        return (-1);
    return (prev_containers + my_num);
}

template <class Container>
void IMerge<Container>::reassess_size()
{
    prev_containers = cur_containers;
    cur_containers = cont_chain.size();
}

//i need to pay attention here never to get out of bounds
template <class Container>
void IMerge<Container>::create_sequence()
{
    reassess_size();
    typename Container::iterator cur = cont_chain[0].begin();
    typename Container::iterator temp = cont_chain[0].begin();
    typename Container::iterator pair_cur = cont_chain[my_pair(0)].begin();
    int ctr = 0;
    size_t old_size = cont_chain[0].size();
    
    while (cont_chain[0].size() > ((old_size / 2) + (old_size % 2)))
    {
        std::cout << "compared " << *cur << " and " << *(cur + 1) << std::endl;
        if (*cur >= *(cur + 1))
        {
            *pair_cur = *cur;
            temp = cur;
            cur++;
            sequence[ctr] = 'F';
        }
        else
        {
            *pair_cur = *(cur + 1);
            temp = cur + 1;
            cur++;
            sequence[ctr] = 'S';
        }
        std::cout << "moved " << *pair_cur << std::endl;
        cur++;
        std::cout << "erasing " << *temp << std::endl;
        cont_chain[0].erase(temp);
        pair_cur++;
        ctr++;
    }
    cont_chain[0].resize((old_size / 2) + (old_size % 2));
}

template <class Container>
void IMerge<Container>::mirror_sequence(int my_num)
{
    typename Container::iterator cur = cont_chain[my_num].begin();
    typename Container::iterator temp = cont_chain[my_num].begin();
    typename Container::iterator pair_cur = cont_chain[my_pair(my_num)].begin();
    int ctr = 0;
    size_t old_size = cont_chain[my_num].size();
    
    while (cont_chain[my_num].size() > ((old_size / 2) + (old_size % 2)))
    {
        std::cout << "compared " << *cur << " and " << *(cur + 1) << std::endl;
        if (sequence[ctr] == 'F')
        {
            *pair_cur = *cur;
            temp = cur;
            cur++;
        }
        else if (sequence[ctr] == 'S')
        {
            *pair_cur = *(cur + 1);
            temp = cur;
            cur++;
        }
        std::cout << "moved " << *pair_cur << std::endl;
        cur++;
        cont_chain[my_num].erase(temp);
        pair_cur++;
        ctr++;
    }
    cont_chain[my_num].resize((old_size / 2) + (old_size % 2));
}

template <class Container>
void IMerge<Container>::take_apart()
{
    //recursion criteria
    depth--;
    if (depth > bottom)
        take_apart();
    //execute actual task
    std::cout << "Depth " << depth << ". Taking apart..." << std::endl;
    cont_chain.setup_next_depth();
    create_sequence();
    int my_num = 1;
    while (my_pair(my_num) != -1)
    {
        mirror_sequence(my_num);
        my_num++;
    }
    return ;
}

template <class Container>
void IMerge<Container>::assemble()
{
    //recursion criteria
    depth--;
    if (depth >= breakpoint)
        assemble();
    if (depth < breakpoint)
        take_apart();
    //execute actual task
    std::cerr << "Depth " << depth << ". Assembling..." << std::endl;
    cont_chain.eliminate_empty_nodes();
}

template <class Container>
void IMerge<Container>::do_sort()
{
    bottom = recursion_levels * 2 * (-1);
    breakpoint = recursion_levels * (-1);

    //cont_chain.setup_next_depth();
    //create_sequence();
    assemble();
}

/*
template <class Container>
void IMerge<Container>::mirror_sequence(int my_num)
{
    typename Container::iterator cur = cont_chain[my_num].begin();
    typename Container::iterator pair_cur = cont_chain[my_pair(my_num)].begin();
    int ctr = 0;
    int old_size = cont_chain[my_num].size();
    
    while (cont_chain[my_num].size() > old_size / 2)
    {
        if (sequence[ctr] == 'F')
        {
            *pair_cur = *cur;
            cur = cont_chain[my_num].erase(cur);
        }
        else if (sequence[ctr] == 'S')
        {
            *pair_cur = *(cur + 1);
            cont_chain[my_num].erase(cur + 1);
        }
        std::cout << "moved " << *pair_cur << std::endl;
        cur++;
        pair_cur++;
        ctr++;
    }
}*/

template <class Container>
void IMerge<Container>::print_content(int my_num)
{
    typename Container::iterator cur = cont_chain[my_num].begin();
    while (cur != cont_chain[my_num].end())
    {
        std::cout << *cur << " ";
        cur++;
    }
    std::cout << std::endl;
    // std::cout << *cur << std::endl; //whyyy
}