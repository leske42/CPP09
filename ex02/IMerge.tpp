/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:52:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/12 22:05:58 by mhuszar          ###   ########.fr       */
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
    argc--;
    while (argc > 1)
    {
        argc /= 2;
        recursion_levels++;
    }
    cur_containers = 1;
    prev_containers = 0;
    depth = 0;
    seq_max = -1;
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

template <class Container>
void IMerge<Container>::create_sequence(Container& cont, Container& pair)
{

    int idx = 0;
    int max_idx = cont.size() - 1;
    int ctr = 0;

    pair.resize(max_idx + 1);
    sequence.resize(max_idx + 1);
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
        std::cout << "moving " << cont[idx] << std::endl;
        sequence[ctr] = idx;
        cont[idx] = DUMMY_VAL;
    }
    pair.resize(idx);
    sequence.resize(ctr);
    seq_max = ctr;
    std::cout << "Sequence size: " << sequence.size() << std::endl;
    std::cout << "Sequence content after creation: ";
    print_content(sequence);
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

    pair.resize(max_idx + 1);
    // print_content(sequence);
    std::cout << "Max index is: " << max_idx << std::endl;
    while (idx <= max_idx)
    {
        // std::cout << "Following seq" << std::endl;
        if (ctr < seq_max && idx == sequence[ctr])
        {
            std::cout << "Moving " << cont[idx] << std::endl;
            pair[ctr] = cont[idx];
            cont[idx] = DUMMY_VAL;
            ctr++; //will this never get out of bounds?
        }
        idx++;
    }
    pair.resize(ctr);
    clear_dummy_vals(cont);
    // int tempsize = sequence.size();
    sequence.clear();
    // std::cout << "Seq content after clear: ";
    print_content(sequence);
    // sequence.resize(tempsize);
}

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
    std::cout << "Num: " << my_num << " pair: " << my_pair(my_num) << std::endl;
    while (my_pair(my_num) != -1)
    {
        follow_sequence(cont_chain[my_num], cont_chain[my_pair(my_num)]);
        my_num++;
    }
    if (my_num == 1) //no "follow" happened
        sequence.clear();
    depth++;
    return ;
}

template <class Container>
void IMerge<Container>::merge_containers(Container& from, Container& to)
{

    std::sort(from.begin(), from.end());
    std::sort(to.begin(), to.end());

    Container temp(from.size() + to.size());

    std::merge(from.begin(), from.end(), to.begin(), to.end(), temp.begin());

    std::cout << "Displaying from content: ";
    typename Container::iterator cur = from.begin();
    while (cur != from.end())
    {
        std::cout << *cur << " ";
        cur++;
    }
    std::cout << std::endl;

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

    int diff = depth - breakpoint;
    std::cerr << "Depth " << depth << ". Assembling..." << std::endl;
    int my_num = 0;
    while (my_pair_up(my_num, diff) != -1)
    {
        std::cout << "Merging " << my_pair_up(my_num, diff) << " into " << my_num << std::endl;
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