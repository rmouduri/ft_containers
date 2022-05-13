#include "../includes_and_utils/tester.hpp"
#include "../each_tests/create_containers.hpp"
#include "../select_your_tests/select_vector_tests.hpp"
#include "../select_your_tests/select_stack_tests.hpp"
#include "../select_your_tests/select_map_tests.hpp"

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

	testVector(arrInt, arrString);
}

void    testVector(const int (&arrInt)[20], const std::string (&arrString)[20])
{
	constructVectorList<int, std::vector<int> >(arrInt, testNotConstVec<std::vector<int> >, testConstVec<const std::vector<int> >);
	constructVectorList<std::string, std::vector<std::string> >(arrString, testNotConstVec<std::vector<std::string> >, testConstVec<const std::vector<std::string> >);
}