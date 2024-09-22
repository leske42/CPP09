/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperationInterrupt.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:42:31 by mhuszar           #+#    #+#             */
/*   Updated: 2024/08/31 18:02:14 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_INTERRUPT_HPP
# define OP_INTERRUPT_HPP

#include <iostream>
#include <exception>

#define PRIMED true
#define UNPRIMED false

class OperationInterrupt : public std::exception
{
    public:

        OperationInterrupt(void);
        OperationInterrupt(bool primer);
        ~OperationInterrupt() throw();
        OperationInterrupt(const OperationInterrupt& other);
        
        bool primed;

    private:

        OperationInterrupt& operator=(const OperationInterrupt& other);
};

#endif