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

	testMap(arrInt, arrString);
}

void    testMap(const int (&arrInt)[20], const std::string (&arrString)[20])
{
	constructMap<int, std::string, ft::map<int, std::string>, ft::pair<int, std::string> >
		(arrInt, arrString, testNotConstMap<ft::map<int, std::string> >, testConstMap<const ft::map<int, std::string> >);
	constructMap<std::string, int, ft::map<std::string, int>, ft::pair<std::string, int> >
		(arrString, arrInt, testNotConstMap<ft::map<std::string, int> >, testConstMap<const ft::map<std::string, int> >);
}