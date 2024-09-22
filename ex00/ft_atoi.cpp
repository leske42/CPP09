/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:01:10 by mhuszar           #+#    #+#             */
/*   Updated: 2024/09/22 13:56:03 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperationInterrupt.hpp"

static int	survey(const char *str)
{
	int	c;
	int	minus_ctr;

	c = 0;
	minus_ctr = 0;
	while ((str[c] > 8 && str[c] < 14) || str[c] == 32)
		c++;
	if (str[c] == 43 || str[c] == 45)
	{
		if (str[c] == 45)
			minus_ctr++;
		c++;
	}
	if (minus_ctr % 2 == 0)
		return (c);
	else
		return (c * -1);
}

long int	ft_atoi(const char *str)
{
	long int	nb;
	int			sign;
	int			start;

	nb = 0;
	if (!str || !str[0])
		throw OperationInterrupt(PRIMED);
	sign = survey(str);
	start = sign;
	if (sign < 0)
		start = start * -1;
	while (str[start] > 47 && str[start] < 58)
	{
		nb = (nb * 10) + str[start] - '0';
		if ((nb > 2147483647 && sign > -1) || (nb > 2147483648 && sign < 0))
			throw OperationInterrupt(PRIMED);
		start++;
	}
	if (sign < 0)
		return (nb * -1);
	else
		return (nb);
}