# include <map>
# include <iostream>
# include "map.hpp"
# include "pair.hpp"

int main()
{
	{
		std::map<std::string, int> map;
		
		map.insert(std::pair<std::string, int>("asadasd", 1));
		map.insert(std::pair<std::string, int>("cdasdasd", 3));
		map.insert(std::pair<std::string, int>("bfeqwf", 2));
		map.insert(std::pair<std::string, int>("asadasd", 4));

		std::map<std::string, int>::iterator it = map.begin();
		while (it != map.end()) {
			std::cout << it->first << ' ' << it->second << '\n';
			it++;
		}
	}
	{
		ft::map<std::string, int> map;

		// map.insert(ft::pair<std::string, int>(std::string("asadasd"), 1));
		// map.insert(ft::pair<std::string, int>(std::string("cdasdasd"), 3));
		// map.insert(ft::pair<std::string, int>(std::string("bfeqwf"), 2));
		// map.insert(ft::pair<std::string, int>(std::string("asadasd"), 4));

		// ft::map<std::string, int>::iterator it = map.begin();
		// while (it != map.end()) {
			// std::cout << it->first << ' ' << it->second << '\n';
			// it++;
			// }
	}
	return 0;
}