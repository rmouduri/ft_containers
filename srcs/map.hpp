#ifndef __MAP_HPP__
# define __MAP_HPP__

#include <iostream>
#include <cstdio>
#include <memory>
#include "pair.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
	class map {

	public:
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef pair<const key_type, mapped_type>	value_type;
		typedef Compare								key_compare;
		typedef less<key_type>						value_compare;
		typedef Alloc								allocator_type;

		typedef value_type &		reference;
		typedef const value_type &	const_reference;
		typedef value_type *		pointer;
		typedef const value_type *	const_pointer;
		typedef std::size_t			size_type;
		typedef	ptrdiff_t			difference_type;

		map();
		~map();

	private:
		allocator_type	_allocator;
		
	public:
	}; // map
} // namespace ft


#endif // __MAP_HPP__