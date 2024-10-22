/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperationInterrupt.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:42:29 by mhuszar           #+#    #+#             */
/*   Updated: 2024/10/05 11:50:58 by mhuszar          ###   ########.fr       */
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