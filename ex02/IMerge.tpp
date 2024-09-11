/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:52:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/11 20:23:27 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <class Container>
IMerge<Container>::IMerge(void)
{

}

template <class Container>
IMerge<Container>::~IMerge(void)
{
    
}

template <class Container>
void IMerge<Container>::intake_sequence(int argc, char **seq)
{
    sequence.resize(argc);
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
    cur_containers = 1;
    prev_containers = 0;
    depth = 0;
    return (recursion_levels);
}

template <class Container>
int IMerge<Container>::my_pair(int my_num)
{
    if (prev_containers + my_num >= cur_containers)
        return (-1);
    return (prev_containers + my_num);
}

template <class Container>
int IMerge<Container>::my_pair_up(int my_num, int diff)
{
    if (diff == 0)
    {
        if (prev_containers + my_num >= cur_containers
            || prev_containers + my_num == my_num)
            return (-1);
        return (prev_containers + my_num);
    }
    if ((prev_containers / 4) + my_num >= cur_containers
        || (prev_containers / 4) + my_num == my_num)
        return (-1);
    return ((prev_containers / 4) + my_num);
}

template <class Container>
void IMerge<Container>::reassess_size()
{
    prev_containers = cur_containers;
    cur_containers = cont_chain.size();
}

// template <class Container>
// void IMerge<Container>::create_sequence()
// {
//     reassess_size();
//     typename Container::iterator cur = cont_chain[0].begin();
//     typename Container::iterator temp = cont_chain[0].begin();
//     typename Container::iterator pair_cur = cont_chain[my_pair(0)].begin();
//     int ctr = 0;
//     size_t old_size = cont_chain[0].size();
    
//     while (cont_chain[0].size() > ((old_size / 2) + (old_size % 2)))
//     {
//         std::cout << "compared " << *cur << " and " << *(cur + 1) << std::endl;
//         if (*cur <= *(cur + 1))
//         {
//             *pair_cur = *cur;
//             temp = cur;
//             cur++;
//             sequence[ctr] = 'F';
//         }
//         else
//         {
//             *pair_cur = *(cur + 1);
//             temp = cur + 1;
//             cur++;
//             sequence[ctr] = 'S';
//         }
//         std::cout << "moved " << *pair_cur << " to " << my_pair(0) << std::endl;
//         cur++;
//         std::cout << "erasing " << *temp << std::endl;
//         cont_chain[0].erase(temp);
//         pair_cur++;
//         ctr++;
//     }
//     cont_chain[0].resize((old_size / 2) + (old_size % 2));
// }

template <class Container>
void IMerge<Container>::create_sequence(Container& cont, Container& pair)
{

    int idx = 0;
    int max_idx = cont.size() - 1;
    int ctr = 0;

    while (idx < max_idx)
    {
        std::cout << "comparing " << cont[idx] << " and " << cont[idx + 1] << ", ";
        if (cont[idx] < cont[idx + 1])
        {
            pair[ctr] = cont[idx];
            sequence[ctr] = idx;
            std::cout << "moving " << cont[idx] << std::endl;
            cont[idx] = DUMMY_VAL;
        }
        else
        {
            pair[ctr] = cont[idx + 1];
            sequence[ctr] = idx + 1;
            std::cout << "moving " << cont[idx + 1] << std::endl;
            cont[idx + 1]  = DUMMY_VAL;
        }
        idx += 2;
        ctr++;
    }
    if (idx == max_idx) //we had uneven numbers
    {
        pair[ctr] = cont[idx];
        sequence[ctr] = idx;
        cont[idx] = DUMMY_VAL;
    }
    clear_dummy_vals(cont);
}

template <class Container>
void IMerge<Container>::clear_dummy_vals(Container& cont)
{
    typename Container::iterator cur = cont.begin();
    while (cur != cont.end())
    {
        if (*cur == DUMMY_VAL)
            cur = cont.erase(cur);
        else
            cur++;
    }
}

template <class Container>
void IMerge<Container>::follow_sequence(Container& cont, Container& pair)
{
    int idx = 0;
    int max_idx = cont.size() - 1;
    int ctr = 0;

    while (idx <= max_idx)
    {
        if (idx == sequence[ctr])
        {
            pair[ctr] = cont[idx];
            cont[idx] = DUMMY_VAL;
            ctr++; //will this never get out of bounds?
        }
        idx++;
    }
    clear_dummy_vals(cont);
    sequence.clear();
}

// template <class Container>
// void IMerge<Container>::mirror_sequence(int my_num)
// {
//     typename Container::iterator cur = cont_chain[my_num].begin();
//     typename Container::iterator temp = cont_chain[my_num].begin();
//     typename Container::iterator pair_cur = cont_chain[my_pair(my_num)].begin();
//     int ctr = 0;
//     size_t old_size = cont_chain[my_num].size();
    
//     while (cont_chain[my_num].size() > ((old_size / 2) + (old_size % 2)))
//     {
//         std::cout << "compared " << *cur << " and " << *(cur + 1) << std::endl;
//         if (sequence[ctr] == 'F')
//         {
//             *pair_cur = *cur;
//             temp = cur;
//             cur++;
//         }
//         else if (sequence[ctr] == 'S')
//         {
//             *pair_cur = *(cur + 1);
//             temp = cur;
//             cur++;
//         }
//         std::cout << "moved " << *pair_cur << " to " << my_pair(my_num) << std::endl;
//         cur++;
//         cont_chain[my_num].erase(temp);
//         pair_cur++;
//         ctr++;
//     }
//     cont_chain[my_num].resize((old_size / 2) + (old_size % 2));
// }

template <class Container>
void IMerge<Container>::take_apart()
{
    depth--;
    if (depth > bottom)
        take_apart();

    std::cout << "Depth " << depth << ". Taking apart..." << std::endl;
    cont_chain.setup_next_depth();
    reassess_size(); //needed for calc of my_pair
    create_sequence(cont_chain[0], cont_chain[my_pair(0)]);
    int my_num = 1;
    while (my_pair(my_num) != -1)
    {
        follow_sequence(cont_chain[my_num], cont_chain[my_pair(my_num)]);
        my_num++;
    }
    depth++;
    return ;
}

template <class Container>
void IMerge<Container>::merge_containers(Container& from, Container& to)
{

    std::sort(from.begin(), from.end());
    std::sort(to.begin(), to.end());

    // to.resize(from.size() + to.size());
    Container temp(from.size() + to.size());

    std::merge(from.begin(), from.end(), to.begin(), to.end(), temp.begin());

    // std::cout << "Displaying temp content: ";
    // typename Container::iterator cur = temp.begin();
    // while (cur != temp.end())
    // {
    //     std::cout << *cur << " ";
    //     cur++;
    // }

    to = temp;
    from.clear();
}

template <class Container>
void IMerge<Container>::assemble()
{
    depth--;
    if (depth > breakpoint)
        assemble();
    else if (depth <= breakpoint)
        take_apart();

    // int pair;
    // if (depth = breakpoint + 1)
    //     pair = my_pair(my_num);
    // else
    //     pair = my_pair_up(my_num);
    int diff = depth - breakpoint;
    std::cout << "Diff is: " << diff << std::endl;
    std::cerr << "Depth " << depth << ". Assembling..." << std::endl;
    int my_num = 0;
    // std::cout << "my num is " << my_num << ", my pair is " << my_pair_up(my_num, diff) << std::endl;
    while (my_pair_up(my_num, diff) != -1)
    {
        std::cout << "Merging " << my_pair_up(my_num, diff) << " into " << my_num << std::endl;
        // std::cout << my_num << " content: ";
        // cont_chain.print_content(my_num);
        // std::cout << my_pair(my_num) << " content: ";
        // cont_chain.print_content(my_pair(my_num));
        merge_containers(cont_chain[my_pair_up(my_num, diff)], cont_chain[my_num]);
        my_num++;
    }
    depth++;
    cont_chain.eliminate_empty_nodes();
    reassess_size();
    return ;
}

template <class Container>
void IMerge<Container>::print_content(Container& cont)
{
    typename Container::iterator cur = cont.begin();
    while (cur != cont.end())
    {
        std::cout << *cur << " ";
        cur++;
    }
    std::cout << std::endl;
}