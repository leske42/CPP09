/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperationInterrupt.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:42:29 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/29 18:22:28 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperationInterrupt.hpp"

OperationInterrupt::OperationInterrupt(void)
{
    primed = false;
}

OperationInterrupt::OperationInterrupt(bool primer)
{
    primed = primer;
}

OperationInterrupt::~OperationInterrupt() throw()
{
    
}

OperationInterrupt::OperationInterrupt(const OperationInterrupt& other)
{
    this->primed = other.primed;
}

// OperationInterrupt& OperationInterrupt::operator=(const OperationInterrupt& other)
// {
    
// }