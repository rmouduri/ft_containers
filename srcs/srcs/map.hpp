#ifndef __MAP_HPP__
# define __MAP_HPP__

// # include <iostream>
// # include <cstdio>
// # include <memory>
# include "pair.hpp"
# include "RBTree.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
	class map {

	public:
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef pair<key_type, mapped_type>			value_type;
		typedef Compare								key_compare;
		typedef std::less<T>						value_compare;
		typedef Alloc								allocator_type;

		typedef value_type &		reference;
		typedef const value_type &	const_reference;
		typedef value_type *		pointer;
		typedef const value_type *	const_pointer;
		typedef std::size_t			size_type;
		typedef	ptrdiff_t			difference_type;

		typedef typename RBTree<T, Compare>::iterator				iterator;
		typedef typename RBTree<T, Compare>::const_iterator			const_iterator;
		// typedef typename RBTree<T, Compare>::reverse_iterator		reverse_iterator;
		// typedef typename RBTree<T, Compare>::const_reverse_iterator	const_reverse_iterator;

	private:
		allocator_type					_allocator;
		key_compare						_comp;
		RBTree<value_type, key_compare>	_data;

	public:
		map(): _comp(), _allocator(), _data() {}

		template<typename InputIt>
		map(InputIt first, InputIt last, const Compare & comparator = Compare(), const Alloc & alloc = Alloc()): _comp(comparator), _allocator(alloc) {
			while (first != last) {
				this->_data.insert(*first);
				++first;
			}
		}

		map(const map & rhs): _comp(rhs._comp), _allocator(rhs._allocator), _data(rhs._data) {}

		~map() {}

		map & operator=(const map & rhs) {
			if (this != &rhs) {
				this->_allocator = rhs._allocator;
				this->_comp = rhs._comp;
				this->_data = rhs._data;
			}
			return *this;
		}

		ft::pair<iterator, bool> insert(const value_type & val) {
			return this->_data.insert(val);
		}
	}; // map
} // namespace ft


#endif // __MAP_HPP__