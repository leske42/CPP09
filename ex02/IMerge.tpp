/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:52:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/03 15:45:26 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <class Container>
IMerge<Container>::IMerge(void)
{
    cont_chain = NULL;
}

template <class Container>
IMerge<Container>::~IMerge(void)
{
    
}

template <class Container>
void IMerge<Container>::intake_sequence(int argc, char ***seq)
{
    int cur_pos = 0;
    while (cur_pos <= argc - 2)
    {
        //std::cout << "Pos: " << cur_pos << std::endl;
        cont_chain[0][cur_pos] = _atoi((*seq)[cur_pos + 1]);
        cur_pos++;
    }
}

template <class Container>
void IMerge<Container>::calculate_depth(int argc)
{
    recursion_levels = 0;
    while (argc > 1)
    {
        argc /= 2;
        recursion_levels++;
    }
    max_containers = recursion_levels * 2;
    cur_containers = 1;
    prev_containers = 0;
    cur_level = 0;
}

template <class Container>
int IMerge<Container>::my_pair(int my_num)
{
    return (prev_containers + my_num + 1);
}

//i need to pay attention here never to get out of bounds
template <class Container>
void IMerge<Container>::create_sequence()
{
    typename Container::iterator cur = cont_chain[0].begin();
    typename Container::iterator pair_cur = cont_chain[my_pair(0)].begin();
    int ctr = 0;
    size_t old_size = cont_chain[0].size();
    
    while (cont_chain[0].size() > old_size / 2)
    {
        if (cur >= cur + 1)
        {
            *pair_cur = *cur;
            cur = cont_chain[0].erase(cur);
            sequence[ctr] = 'F';
        }
        else
        {
            *pair_cur = *(cur + 1);
            cont_chain[0].erase(cur + 1);
            sequence[ctr] = 'S';
        }
        cur++;
        pair_cur++;
        ctr++;
    }
}

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
        cur++;
        pair_cur++;
        ctr++;
    }
}