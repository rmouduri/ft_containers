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

	const std::string arrString[20] = {"hello cocos", "j'arrive", "oui-oui", "kafeolait", 
										"jul d'ananas", "jul d'ananas", "42", "jura", 
										"saperlipopette", "anticonstitutionnellement", 
										"Pneumonoultramicroscopicsilicovolcanoconiosis", "Blue", 
										"Red", "Orange", "Yellow", "boulette de viande hache",
										"raviolis du nord est", "PNY", "street bangkok", "confifi"};

	testVector(arrInt, arrString);
}

void    testVector(const int (&arrInt)[20], const std::string (&arrString)[20])
{
	constructVectorList<int, ft::vector<int> >(arrInt, testNotConstVec<ft::vector<int> >, testConstVec<const ft::vector<int> >);
	constructVectorList<std::string, ft::vector<std::string> >(arrString, testNotConstVec<ft::vector<std::string> >, testConstVec<const ft::vector<std::string> >);
}