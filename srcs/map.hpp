#ifndef __MAP_HPP__
# define __MAP_HPP__

// # include <iostream>
// # include <cstdio>
// # include <memory>
# include "pair.hpp"
# include "BTree.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<Key, T> > >
	class map {

	public:
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef pair<const key_type, mapped_type>	value_type;
		typedef Compare								key_compare;
		typedef Alloc								allocator_type;

		typedef value_type &		reference;
		typedef const value_type &	const_reference;
		typedef value_type *		pointer;
		typedef const value_type *	const_pointer;
		typedef std::size_t			size_type;
		typedef	ptrdiff_t			difference_type;

		typedef typename BTree<value_type, Compare, Alloc>::iterator				iterator;
		typedef typename BTree<value_type, Compare, Alloc>::const_iterator			const_iterator;
		typedef typename BTree<value_type, Compare, Alloc>::reverse_iterator		reverse_iterator;
		typedef typename BTree<value_type, Compare, Alloc>::const_reverse_iterator	const_reverse_iterator;

	private:
		key_compare								_comp;
		allocator_type							_allocator;
		BTree<value_type, key_compare, Alloc>	_data;

	public:
		class value_compare {
			protected:
				Compare comp;

			public:
				value_compare(Compare c): comp(c) {}
				~value_compare() {}

				bool operator()(const value_type & x, const value_type & y) const { return comp(x.first, y.first); }
		}; // value_compare

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

		iterator insert (iterator position, const value_type & val) {
			return this->_data.insert(position, val);
		}

		template<typename InputIt>
		void insert(InputIt first, InputIt last) {
			_data.insert(first, last);
		}

		iterator begin() { return this->_data.begin(); }
		const_iterator begin() const { return this->_data.begin(); }

		iterator end() { return this->_data.end(); }
		const_iterator end() const { return this->_data.end(); }

		reverse_iterator rbegin() { return this->_data.rbegin(); }
		const_reverse_iterator rbegin() const { return this->_data.rbegin(); }

		reverse_iterator rend() { return this->_data.rend(); }
		const_reverse_iterator rend() const { return this->_data.rend(); }

		size_type size() const { return this->_data.getSize(); }

		size_type max_size() const { return this->_data.getMaxSize(); }

		iterator find(const key_type & k) { return iterator(this->_data.findNode(this->_data._getRoot(), ft::make_pair(k, T()))); }

		const_iterator find(const key_type & k) const { return const_iterator(this->_data.findNode(this->_data._getRoot(), ft::make_pair(k, T()))); }

		mapped_type & operator[](const key_type & k) {
			iterator it = this->find(k);

			if (it != this->_data.end())
				return it->second;
			else
				return this->insert(ft::make_pair(k, T())).first->second;
		}

		key_compare key_comp() const { return this->_comp; }

		value_compare value_comp() const { return value_compare(this->_comp); }

		bool empty() const { return !this->_data.getSize(); }

		allocator_type get_allocator() const { return this->_allocator; }

		size_type count(const key_type & k) const {
			const_iterator it = this->find(k);

			return it != this->end();
		}

		void swap(map & rhs) {
			if (this != &rhs)
				this->_data.swap(rhs._data);
		}

		void clear() { this->_data.clear(this->_data._getRoot()); }

		size_t erase(const key_type & k) { return _data.erase(this->_data.findNode(this->_data._getRoot(), ft::make_pair(k, T()))); }

		void erase(iterator pos) { _data.erase(pos); }

		void erase(iterator first, iterator last) { _data.erase(first, last); }

		iterator lower_bound(const key_type & k) { return _data.lower_bound(ft::make_pair(k, typename value_type::second_type())); }

		const_iterator lower_bound(const key_type & k) const { return _data.lower_bound( ft::make_pair(k, typename value_type::second_type())); }

		iterator upper_bound(const key_type & k) { return _data.upper_bound(ft::make_pair(k, typename value_type::second_type())); }

		const_iterator upper_bound(const key_type & k) const { return _data.upper_bound(ft::make_pair(k, typename value_type::second_type())); }

		ft::pair<iterator, iterator> equal_range(const key_type & k) { return _data.
																				equal_range(
																				ft::make_pair(
																				k,
																				typename value_type::second_type())); }

		ft::pair<const_iterator, const_iterator> equal_range(const key_type & k) const { return _data.
																							equal_range(
																							ft::make_pair(
																							k, 
																							typename value_type::second_type())); }

		friend bool operator==(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) { return lhs._data == rhs._data; }

		friend bool operator!=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) { return lhs._data != rhs._data; }

		friend bool operator<(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) { return lhs._data < rhs._data; }

		friend bool operator>(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs) { return lhs._data > rhs._data; }

		friend bool operator<=(const ft::map<Key, T, Compare, Alloc> & lhs,  const ft::map<Key, T, Compare, Alloc> & rhs) { return lhs._data <= rhs._data; }

		friend bool operator>=(const ft::map<Key, T, Compare, Alloc> & lhs,  const ft::map<Key, T, Compare, Alloc> & rhs) { return lhs._data >= rhs._data; }

		private:
			void print2d() { this->_data.print2D(); }
	}; // map
} // namespace ft


#endif // __MAP_HPP__