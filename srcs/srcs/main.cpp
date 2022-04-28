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

		std::map<std::string, int>::reverse_iterator rit = map.rbegin();
		int i = 0;
		while (rit != map.rend()) {
			std::cout << rit->first << ' ' << rit->second << '\n';
			--rit;
			std::cout << "i: " << i << '\n';
			if (++i > 10)
				break ;
		}
	}
	{
		ft::map<int, int> map;

		for (int i = 0; i < 30; ++i)
			map.insert(ft::pair<int, int>(i, i));


		ft::map<int, int>::iterator it = map.begin();
		ft::map<int, int>::const_iterator cit(it);


		// map.printinorder();
		// map.print2d();
		while (it != map.end()) {
			std::cout << it->first << ' ' << it->second << '\n';
			it++;
		}
	}
	return 0;
}