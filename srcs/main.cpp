#include <iostream>
#include <vector>
#include <iterator>
#include "vector.hpp"

// using namespace ft;

int main(void)
{
	{
		std::vector<int> vec1(4);
		ft::vector<int> vec2(4);

		std::cout << "std = " << vec1.size() << " | "
						<< "ft = " << vec2.size() << '\n';
		vec1.resize(10);
		vec2.resize(10);
		
		std::cout << "std = " << vec1.size() << " | "
						<< "ft = " << vec2.size() << '\n';


		for (int i = 0; i < 4; ++i)
			std::cout << "std[" << i << "] = " << vec1[i] << " | "
						<< "ft[" << i << "] = " << vec2[i] <<	'\n';
		}

	return 0;
}