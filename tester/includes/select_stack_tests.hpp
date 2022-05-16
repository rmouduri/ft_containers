/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_stack_tests.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:51:32 by llefranc          #+#    #+#             */
/*   Updated: 2022/05/16 10:25:35 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_STACK_TESTS_HPP
#define SELECT_STACK_TESTS_HPP

#include "stack_tests.hpp"

template <typename T>
void    testNonConstStack(T& s, int testNb)
{
    printContainerInfo<T>("STACK", testNb);
        
    stackTest_Size(s);                          //  size
    stackTest_Empty(s);                         //  empty
    stackTest_Top(s);                           //  top
    stackTest_Pop(s);                           //  pop
    stackTest_Push(s);                          //  push
    stackTest_OperatorEqualNotEqual(s);         //  == / !=
    stackTest_OperatorLessAndMore(s);           //  < / <= / > / >=
}

#endif
