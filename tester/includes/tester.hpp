#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>

#include "../includes/include_your_files.hpp"

// Needed for testing
// #include "stl_like.hpp"
#include "utils.hpp"
#include "print_type.hpp"

void    testVector(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testList(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testStack(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testQueue(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testMap(const int (&arrInt)[20], const std::string (&arrString)[20]);

#endif