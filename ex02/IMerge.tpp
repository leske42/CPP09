/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:52:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/31 19:18:55 by mhuszar          ###   ########.fr       */
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
void IMerge<Container>::intake_sequence(int argc, char **seq)
{
    int cur_pos = 0;
    while (cur_pos <= argc - 2)
    {
        cont_chain[0][cur_pos] = _atoi(seq[cur_pos - 1]);
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
    cur_level = 0;
}