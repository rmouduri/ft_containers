#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include "iterators.hpp"
# include "const_it.hpp"
# include "input_iterator.hpp"
# include "random_access_iterator.hpp"
# include "rev_const_it.hpp"
# include "rev_random_access_iterator.hpp"
# include "enable_if.hpp"
# include "equal.hpp"

namespace ft {

	template< class T, class Alloc = std::allocator<T> >
	class vector {		
	
	public:
		typedef T														value_type;
		typedef size_t													size_type;
		typedef std::allocator<value_type>								allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::random_access_iterator<T, 0>						iterator;
		typedef ft::const_it<T, 1>										const_iterator;
		typedef ft::rev_random_access_iterator<T, 2>					reverse_iterator;
		typedef ft::rev_const_it<T, 3>									const_reverse_iterator;
		typedef ptrdiff_t												difference_type;

	private:
		allocator_type	_allocator;
		size_type		_cap;
		size_type		_size;
		pointer			_start;

	public:

		//////////////////////// Constructors/Destructors ////////////////////////

		explicit vector(const allocator_type& alloc = allocator_type()) : _allocator(alloc), _cap(0), _size(0), _start(0) {}
		
		explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()):
			_allocator(alloc), _cap(n), _size(n) {
			this->_start = _allocator.allocate(this->_cap);
			for (size_type i = 0; i < n; i++){
				this->_allocator.construct(&this->_start[i], val);
			}
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<ft::is_integral<InputIterator>::value == 0>::type * = 0):
			_allocator(alloc), _cap(0), _size(0), _start(0) {
			while (first != last) {
				reserve(this->_size + 1);
				this->_allocator.construct(&this->_start[this->_size], *first);
				++first;
				++this->_size;
			} 
		}

		vector(const vector & newVector) :
			_allocator(newVector._allocator), _cap(newVector._cap), _size(newVector._size), _start(_allocator.allocate(_cap)) {
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(&_start[i], newVector._start[i]);
		}

		~vector() {
			this->clear();
			this->_allocator.deallocate(this->_start, this->_cap);
		}

		vector & operator=(const vector & newVector) {
			this->_allocator = newVector._allocator;
			this->_cap = newVector._cap;
			this->_size = newVector._size;
			this->_start = this->_allocator.allocate(_cap);
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(&_start[i], newVector._start[i]);
			return *this;
		}


		//////////////////////// Iterators ////////////////////////

		iterator begin() { return iterator(this->_start); }
		const_iterator begin() const { return const_iterator(this->_start); }

		iterator end() { return this->_start + this->_size; }
		const_iterator end() const { return this->_start + this->_size; }

		reverse_iterator rbegin() { return this->end(); }
		const_reverse_iterator rbegin() const { return this->end(); }

		reverse_iterator rend() { return this->begin(); }
		const_reverse_iterator rend() const { return this->begin(); }


		//////////////////////// Capacity ////////////////////////

		size_type size() const { return this->_size; }
		size_type max_size() const { return this->_allocator.max_size(); }

		void resize(size_type n, value_type val = value_type()) {
			if (n < this->_size) {
				for (size_t i = n; i < this->_size; ++i)
					this->_allocator.destroy(this->_start + i);
				this->_size = n;
			}
			else if (n > this->_size) {
				if (n > this->_cap)
					this->reserve(n);
				for (size_type i = this->_size; i < n; ++i)
					this->_allocator.construct(this->_start + i, val);
				this->_size = n;
			}
		}

		size_type capacity() const { return this->_cap; }

		bool empty() const { return !this->_size; }

		void reserve(size_type newCap) {
			if (this->_cap >= newCap)
				return;
			if (newCap >= this->max_size())
				throw std::length_error("newCap is greater than max_size");

			pointer newStart = _allocator.allocate(newCap);

			for (size_type i = 0; i < size(); ++i) {
				_allocator.construct(newStart + i, _start[i]);
				_allocator.destroy(_start + i);
			}
			this->_allocator.deallocate(_start, _cap);
			this->_start = newStart;
			this->_cap = newCap;
		}


		//////////////////////// Element access ////////////////////////

		reference operator[](size_t i) { return this->_start[i]; }
		const_reference operator[](size_t i) const { return this->_start[i]; }

		reference at(size_t i) { 
			if (i >= this->_size)
				throw std::out_of_range("vector: index out of range");	
			return this->_start[i];
		}

		const_reference at(size_t i) const { 
			if (i >= this->_size)
				throw std::out_of_range("vector: index out of range");	
			return this->_start[i];
		}

		reference front() { return *this->_start; }
		const_reference front() const { return *this->_start; }

		reference back() { return this->_start[this->_size - 1]; }
		const_reference back() const { return this->_start[this->_size - 1]; }


		//////////////////////// Modifiers ////////////////////////

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
			typename ft::enable_if<ft::is_integral<InputIterator>::value == 0>::type* = 0) {
			size_type n = 0;

			for (InputIterator firstCopy = first, lastCopy = last; firstCopy != lastCopy; ++firstCopy)
				++n;
			this->clear();
			if (this->_cap < n)
				this->reserve(n);
			for (size_type i = 0; i < n; ++i, ++first)
				this->_allocator.construct(&this->_start[i], *first);
			this->_size = n;
			this->_cap = n > this->_cap ? n : this->_cap;
		}

		void assign(size_type n, const value_type& val) {
			this->clear();
			if (this->_cap < n)
				this->reserve(n);
			for (size_type i = 0; i < n; ++i)
				this->_allocator.construct(&this->_start[i], val);
			this->_size = n;
			this->_cap = n > this->_cap ? n : this->_cap;
		}

		void push_back(const value_type& val) {
			if (this->_size == this->_cap)
				this->reserve(this->_cap ? this->_cap * 2 : 1);
			this->_allocator.construct(this->_start + this->_size++, val);
		}

		void pop_back(void) { this->_allocator.destroy(this->_start + --this->_size); }

		iterator insert(iterator position, const value_type & val) {
			size_type pos = position - this->begin();

			this->push_back(val);
			for (size_type i = this->end() - this->begin(); i > pos + 1;) {
				--i;
				this->_start[i] = this->_start[i - 1];
			}

			this->_start[pos] = val;

			return iterator(this->_start + pos);
		}

		void insert(iterator position, size_type n, const value_type & val) {
			size_type pos = position - this->begin();

			if (!n)
				return ;
			if (this->_size + n > this->_cap) {
				if (this->_size + n > this->_cap * 2)
					this->reserve(this->_size + n);
				else
					this->reserve(this->_cap * 2);
			}

			if (this->_size > 0 && pos != this->_size) {
				for (size_type i = this->_size - 1; i >= pos; --i) {
					if (i + n >= this->_size)
						this->_allocator.construct(this->_start + i + n, this->_start[i]);
					else this->_start[i + n] = this->_start[i];

					if (i == pos)
						break;
				}
			}

			for (size_type i = pos; i != pos + n; ++i) {
				if (i >= this->_size)
					this->_allocator.construct(this->_start + i, val);
				else this->_start[i] = val;
			}
			this->_size += n;
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<ft::is_integral<InputIterator>::value == 0>::type* = 0)
		{
			size_type pos = position - this->begin();
			size_type n = 0;

			for (InputIterator firstCopy = first; firstCopy != last; ++firstCopy)
				++n;

			if (!n)
				return ;

			if (this->_size + n > this->_cap) {
				if (this->_size + n > this->_cap * 2)
					this->reserve(this->_size + n);
				else
					this->reserve(this->_cap * 2);
			}

			if (this->_size > 0 && pos != this->_size) {
				for (size_type i = this->_size - 1; i >= pos; --i) {
					if (i + n >= this->_size)
						this->_allocator.construct(this->_start + i + n, this->_start[i]);
					else this->_start[i + n] = this->_start[i];

					if (i == pos)
						break;
				}
			}

			for (size_type i = pos; i != pos + n; ++i, ++first) {
				if (i >= this->_size)
					this->_allocator.construct(this->_start + i, *first);
				else this->_start[i] = *first;
			}
			this->_size += n;
		}

		iterator erase(iterator position) {
			erase(position, position + 1);

			return position;

		}

		iterator erase(iterator first, iterator last) {
			size_type dist = last - first;
			size_type ret = first - this->begin();

			for (; first + dist < this->end(); ++first, ++last)
				*first = *(first + dist);
			for (; first != this->end(); ++first)
				this->_allocator.destroy(&(*first));
			this->_size -= dist;
			return this->begin() + ret;
		}

		void swap(vector & x) {
			swap(this->_allocator, x._allocator);
			swap(this->_size, x._size);
			swap(this->_cap, x._cap);
			swap(this->_start, x._start);
		}

		void clear(void) {
			for (size_type i = 0; i != _size; ++i)
				this->_allocator.destroy(this->_start + i);

			this->_size = 0;
		}


		//////////////////////// Allocator ////////////////////////

		allocator_type get_allocator(void) const { return this->_allocator; }


		//////////////////////// Relational Operators ////////////////////////

		friend bool operator==(const vector & lhs, const vector & rhs) {
			if (lhs.size() != rhs.size())
				return false;
			vector tmpl = lhs;
			vector tmpr = rhs;
			return ft::equal(tmpl.begin(), tmpl.end(), tmpr.begin());
		}

		friend bool operator!=(const vector & lhs, const vector & rhs) {
			if (lhs.size() != rhs.size())
				return true;
			vector tmpl = lhs;
			vector tmpr = rhs;
			return !(ft::equal(tmpl.begin(), tmpl.end(), tmpr.begin()));
		}

		friend bool operator<(const vector & lhs, const vector & rhs) {
			if (lhs.size() < rhs.size())
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		friend bool operator<=(const vector & lhs, const vector & rhs) { return !(rhs < lhs); }

		friend bool operator>(const vector & lhs, const vector & rhs) { return (rhs < lhs); }

		friend bool operator>=(const vector & lhs, const vector & rhs) { return !(lhs < rhs); }


		//////////////////////// Other ////////////////////////

		void swap(vector & x, vector & y) { x.swap(y); }

	private:
		template<typename U>
		void	swap(U &x, U &y){
			if (&x == &y)
				return ;
			U tmp = x;
			x = y;
			y = tmp;
		}
	};

} // namespace ft

# endif // __VECTOR_HPP__