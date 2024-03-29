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
