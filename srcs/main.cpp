# include <map>

# include <list>

# include <iostream>
# include "map.hpp"
# include "pair.hpp"


template <typename T>
void print(T rit) {
	std::cout << rit->first << '\t' << rit->second << '\n';
}

int main(void) {
	ft::map<float, int> map;

	map[2.5] = 7;
	map[1.5] = 14;
	map[0.5] = 21;
	map[-0.5] = 28;
	map[-1.5] = 35;

	{
		ft::map<float, int>::iterator it = map.begin(), ite = map.end();

		while (it != ite) {
			std::cout << '(' << it->first << ':' << it->second << "):\n\tparent: ";
			if (it.getCurrent()->parent) {
				std::cout << '(' << it.getCurrent()->parent->data.first << ':' << it.getCurrent()->parent->data.first << ")\n\tleft: ";
			} else std::cout << "No Parent\n\tleft: ";
			if (it.getCurrent()->left) {
				std::cout << '(' << it.getCurrent()->left->data.first << ':' << it.getCurrent()->left->data.first << ")\n\tright: ";
			} else std::cout << "No Left\n\tright: ";
			if (it.getCurrent()->right) {
				std::cout << '(' << it.getCurrent()->right->data.first << ':' << it.getCurrent()->right->data.first << ")\n";
			} else std::cout << "No Right\n";
			++it;
		}
	}
	ft::map<float, int>::reverse_iterator rit = map.rbegin(), rite = map.rend();

	while (rit != rite) {
		std::cout << rit->first << ':' << rit->second << " from " << rit.getCurrent()->data.first << ':' << rit.getCurrent()->data.second << std::endl;
		++rit;
	}
	std::cout << std::endl;

	ft::map<float, int>::iterator it = map.begin(), ite = map.end();
	--it;
	while (--ite != it) {
		std::cout << '(' << ite->first << ':' << ite->second << "):\n\tparent: ";
			if (ite.getCurrent()->parent) {
				std::cout << '(' << ite.getCurrent()->parent->data.first << ':' << ite.getCurrent()->parent->data.first << ")\n\tleft: ";
			} else std::cout << "No Parent\n\tleft: ";
			if (ite.getCurrent()->left) {
				std::cout << '(' << ite.getCurrent()->left->data.first << ':' << ite.getCurrent()->left->data.first << ")\n\tright: ";
			} else std::cout << "No Left\n\tright: ";
			if (ite.getCurrent()->right) {
				std::cout << '(' << ite.getCurrent()->right->data.first << ':' << ite.getCurrent()->right->data.first << ")\n";
			} else std::cout << "No Right\n";
	}

	return 0;
}