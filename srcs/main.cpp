# include <map>
# include <iostream>
# include "map.hpp"
# include "pair.hpp"
// # include "vector.hpp"

int main()
{
	{
		std::map<std::string, int> map;

		map.insert(std::pair<std::string, int>("asadasd", 1));
		map.insert(std::pair<std::string, int>("cdasdasd", 3));
		map.insert(std::pair<std::string, int>("bfeqwf", 2));
		std::pair<std::map<std::string, int>::iterator, bool> oui = map.insert(std::pair<std::string, int>("asadasd", 4));

		std::cout << oui.second << oui.first->second << '\n';
		std::map<std::string, int>::iterator it = map.begin();
		int i = 0;
		while (it != map.end()) {
			std::cout << it->first << ' ' << it->second << '\n';
			++it;
		}
	}
	{
		ft::map<int, int> map;

		for (int i = 0; i < 5; ++i)
			map.insert(ft::pair<int, int>(i, i));

		map.insert(ft::pair<int, int>(10, 10));
		ft::map<int, int>::reverse_iterator it = map.rbegin();

		// it->second = 10;
		// it->first = 10;
		// map.print2d();
		while (it != map.rend()) {
			std::cout << it->first << ' ' << it->second << '\n';
			it++;
		}
	}
	return 0;
}