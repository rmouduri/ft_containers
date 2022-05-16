#include "../includes/tester.hpp"
#include "../includes/create_containers.hpp"
#include "../includes/select_vector_tests.hpp"
#include "../includes/select_stack_tests.hpp"
#include "../includes/select_map_tests.hpp"

int main(void)
{
	const int arrInt[20] = {58966, 2147483647, 256, -2147483648, 0, 
							-1, 2, 3, 4, 5, 6, 7, 7, 8, 54634152, 9, 
							10, 11, 56, 56465};

	const std::string arrString[20] = {"hello coco", "j'arrive", "oui-oui", "kafeolait", 
										"jul d'ananas", "jul d'ananas", "42", "jura", 
										"saperlipopette", "anticonstitutionnellement", 
										"Pneumonoultramicroscopicsilicovolcanoconiosis", "Blue", 
										"Red", "Orange", "Yellow", "boulette de viande hache",
										"raviolis du nord est", "PNY", "street bangkok", "confifi"};

	testStack(arrInt, arrString);
}

void    testStack(const int (&arrInt)[20], const std::string (&arrString)[20])
{
	constructStackQueue<int, std::stack<int, std::list<int> >, std::list<int> >(arrInt, testNonConstStack<std::stack<int, std::list<int> > >);
	constructStackQueue<std::string, std::stack<std::string, std::list<std::string> >, std::list<std::string> > (arrString, testNonConstStack<std::stack<std::string, std::list<std::string> > >);
}