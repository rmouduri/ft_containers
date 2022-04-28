#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>
#include <iterator>
#include <limits>
#include "iterators.hpp"
#include "enable_if.hpp"

namespace ft
{
	template<typename T, int B>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type const &	const_reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type const *	const_pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;
		protected:
			pointer current;
		public:
		random_access_iterator() : current(pointer()) {}

		random_access_iterator(pointer p) : current(p) {}

		random_access_iterator(const random_access_iterator& x) : current(x.current) {}

		pointer getCurrent() const {
			return (this->current);
		}
		// template<typename U>
		// random_access_iterator(const random_access_iterator<U>& other) : t(other.getT()){
		// 	current = other.getCurrent();
		// }

		// value_type getT() const {return value_type();}

		// operator random_access_iterator<const value_type>() const {return random_access_iterator<const value_type>(current);}

		random_access_iterator base() {
			return current;
		}
		
		template<int U>
		bool operator!=(const random_access_iterator<T, U>& it) const {return (current != it.getCurrent());};
		template<int U>
		bool operator==(const random_access_iterator<T, U>& it) const {return (current == it.getCurrent());};
		template<int U>
		bool operator>(const random_access_iterator<T, U>& it) const {return (current > it.getCurrent());};
		template<int U>
		bool operator<(const random_access_iterator<T, U>& it) const {return (current < it.getCurrent());};
		template<int U>
		bool operator<=(const random_access_iterator<T, U>& it) const {return (current <= it.getCurrent());};
		template<int U>
		bool operator>=(const random_access_iterator<T, U>& it) const {return (current >= it.getCurrent());};

		// bool operator!=(const random_access_iterator<T, 0>& it) const {return (current != it.getCurrent());};
		// bool operator==(const random_access_iterator<T, 0>& it) const {return (current == it.getCurrent());};
		// bool operator>(const random_access_iterator<T, 0>& it) const {return (current > it.getCurrent());};
		// bool operator<(const random_access_iterator<T, 0>& it) const {return (current < it.getCurrent());};
		// bool operator<=(const random_access_iterator<T, 0>& it) const {return (current <= it.getCurrent());};
		// bool operator>=(const random_access_iterator<T, 0>& it) const {return (current >= it.getCurrent());};



		reference operator*() {
			return *current;
		}

		const_reference operator*() const {
			return *current;
		}

		pointer	operator->(){
			return current;
		}

		const_pointer	operator->() const{
			return current;
		}

		random_access_iterator	&operator=(const random_access_iterator &rhs) {
			current = rhs.current;
			return *this;
		}

		random_access_iterator &operator++(){
			++current;
			return *this;
		}

		random_access_iterator operator++(int){
			pointer tmp = current++;
			return tmp;
		}

		random_access_iterator &operator--(){
			--current;
			return *this;
		}

		random_access_iterator operator--(int){
			pointer tmp = current--;
			return tmp;
		}

		difference_type operator-(const random_access_iterator &sub) const{
			difference_type i = 0;
			pointer tmp(current);
			while(tmp != sub.current)
			{
				if (tmp > sub.current) {
					tmp--;
					i++;
				}
				else {
					tmp++;
					i--;
				}
			}
			return i;
		}

		random_access_iterator	operator-(difference_type n) const{
			pointer tmp = current;
			for (difference_type i = 0; i < n; i++){
				tmp--;
			}
			return tmp;
		}

		random_access_iterator	operator+(difference_type n) const{
			pointer tmp = current;
			for (difference_type i = 0; i < n; i++){
				tmp++;
			}
			return tmp;
		}

		random_access_iterator	&operator+=(difference_type n){
			for (difference_type i = 0; i < n; i++){
				current++;
			}
			return *this;
		}

		random_access_iterator	&operator-=(difference_type n){
			for (difference_type i = 0; i < n; i++){
				current--;
			}
			return *this;
		}

		reference	operator[](int n){
			return current[n];
		}
		friend random_access_iterator operator+(int lhs, random_access_iterator rhs){
			random_access_iterator tmp(rhs);
			tmp += lhs;
			return tmp;
		}
	};
}

#endif