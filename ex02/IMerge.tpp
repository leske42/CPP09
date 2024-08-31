/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMerge.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:52:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/31 18:14:18 by mhuszar          ###   ########.fr       */
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
    int cur_pos = 0;
    //Container::iterator iter = Container.begin();
    while (cur_pos <= argc - 2)
    {
        //Container.insert(iter, _atoi(seq[cur_pos - 1]));
        // iter++;
        cont[cur_pos] = _atoi(seq[cur_pos - 1]);
        cur_pos++;
    }
}