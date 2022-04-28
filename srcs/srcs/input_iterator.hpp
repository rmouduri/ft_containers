#ifndef INPUT_ITERATOR_HPP
# define INPUT_ITERATOR_HPP

#include "iterators.hpp"

namespace ft
{
	template<typename Iterator, typename Container>
	class InputIterator
	{
	private:
	protected:
		Iterator current;
	public:
		typedef iterator_traits<Iterator> traits_type;
		typedef Iterator									iterator_type;
		typedef typename traits_type::value_type			value_type;
		typedef typename traits_type::difference_type		difference_type;
		typedef typename traits_type::reference			reference;
		typedef typename traits_type::pointer				pointer;
		typedef typename traits_type::iterator_category	iterator_category;
		
		InputIterator(const InputIterator&x) : current(x) { }
		InputIterator	&operator=(const InputIterator&x){
			this->current = x;
		}
		~InputIterator();

		reference operator*(){
			return *current;
		}

		pointer	operator->(){
			return current;
		}

		InputIterator operator++(){
			return ++current;
		}

		InputIterator operator++(int){
			Iterator tmp = current++;
			return tmp;
		}
	};
}

#endif