#ifndef __STACK_HPP__
# define __STACK_HPP__

# include "vector.hpp"

namespace ft {
	template<typename T, typename Container =  ft::vector<T> >
	class stack {
		protected:
			Container c;

		public:
			typedef typename Container::value_type	value_type;
			typedef Container						container_type;
			typedef typename Container::size_type	size_type;

		explicit stack(const container_type & ctnr = container_type()): c(ctnr) {}

		bool empty(void) const { return c.empty(); }

		size_type size(void) const { return c.size(); }

		value_type & top(void) { return c.back(); }

		const value_type & top(void) const { return c.back(); }

		void push(const value_type & val) { c.push_back(val); }

		void pop(void) { c.pop_back(); }

		friend bool operator==(const ft::stack<T, Container> & lhs, const ft::stack<T, Container> & rhs) { return lhs.c == rhs.c; }
		friend bool operator!=(const ft::stack<T, Container> & lhs, const ft::stack<T, Container> & rhs) { return lhs.c != rhs.c; }
		friend bool operator<(const ft::stack<T, Container> & lhs, const ft::stack<T, Container> & rhs) { return lhs.c < rhs.c; }
		friend bool operator<=(const ft::stack<T, Container> & lhs, const ft::stack<T, Container> & rhs) { return lhs.c <= rhs.c; }
		friend bool operator>(const ft::stack<T, Container> & lhs, const ft::stack<T, Container> & rhs) { return lhs.c > rhs.c; }
		friend bool operator>=(const ft::stack<T, Container> & lhs, const ft::stack<T, Container> & rhs) { return lhs.c >= rhs.c; }

	}; // stack
} // namespace ft

# endif // __STACK_HPP__