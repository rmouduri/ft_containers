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
	std::map<float, int> map;

	std::map<float, int>::iterator it = map.begin(), ite = map.end();

	std::cout << it->first << ' ' << it->second << std::endl;
	// while (it != ite) {
		// std::cout << '(' << it->first << ':' << it->second << "):\n\tparent: ";
		// if (it.getCurrent()->parent) {
			// std::cout << '(' << it.getCurrent()->parent->data.first << ':' << it.getCurrent()->parent->data.first << ")\n\tleft: ";
		// } else std::cout << "No Parent\n\tleft: ";
		// if (it.getCurrent()->left) {
			// std::cout << '(' << it.getCurrent()->left->data.first << ':' << it.getCurrent()->left->data.first << ")\n\tright: ";
		// } else std::cout << "No Left\n\tright: ";
		// if (it.getCurrent()->right) {
			// std::cout << '(' << it.getCurrent()->right->data.first << ':' << it.getCurrent()->right->data.first << ")\n";
		// } else std::cout << "No Right\n";
		// ++it;
	// }

	return 0;
}