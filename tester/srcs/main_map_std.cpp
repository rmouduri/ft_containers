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

	testMap(arrInt, arrString);
}

void    testMap(const int (&arrInt)[20], const std::string (&arrString)[20])
{
	constructMap<int, std::string, std::map<int, std::string>, std::pair<int, std::string> >
		(arrInt, arrString, testNotConstMap<std::map<int, std::string> >, testConstMap<const std::map<int, std::string> >);
	constructMap<std::string, int, std::map<std::string, int>, std::pair<std::string, int> >
		(arrString, arrInt, testNotConstMap<std::map<std::string, int> >, testConstMap<const std::map<std::string, int> >);
}