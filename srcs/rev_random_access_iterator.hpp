#ifndef REV_RANDOM_ACCESS_ITERATOR_HPP
# define REV_RANDOM_ACCESS_ITERATOR_HPP

#include "random_access_iterator.hpp"

namespace ft{
	template<typename T, int B>
	class rev_random_access_iterator : public random_access_iterator<T, B>
	{
	public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type const &			const_reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type const *				const_pointer;
	protected:
	public:
		
		rev_random_access_iterator() {
			this->current = pointer();
		}

		rev_random_access_iterator(pointer p) {
			this->current = p;
		}

		rev_random_access_iterator(const random_access_iterator<T, 0>& y){
			this->current = (y.getCurrent() - 1);
		}

		rev_random_access_iterator(const random_access_iterator<T, 2>& y){
			this->current = y.getCurrent();
		}

		pointer getCurrent() const{
			return (this->current);
		}
		// template<typename U>
		// rev_random_access_iterator(const rev_random_access_iterator<U>& other) : t(other.getT()){
		// 	this->current = const_cast<value_type*>(other.getCurrent());
		// }

		// value_type getT() const {return value_type();}

		// operator rev_random_access_iterator<const value_type>() const {return rev_random_access_iterator<const value_type>(this->current);}


		bool operator!=(const random_access_iterator<T, 0>& it) const {return (this->current != it.getCurrent());};
		bool operator==(const random_access_iterator<T, 0>& it) const {return (this->current == it.getCurrent());};
		bool operator>(const random_access_iterator<T, 0>& it) const {return (this->current < it.getCurrent());};
		bool operator<(const random_access_iterator<T, 0>& it) const {return (this->current > it.getCurrent());};
		bool operator<=(const random_access_iterator<T, 0>& it) const {return (this->current >= it.getCurrent());};
		bool operator>=(const random_access_iterator<T, 0>& it) const {return (this->current <= it.getCurrent());};

		bool operator!=(const random_access_iterator<T, 2>& it) const {return (this->current != it.getCurrent());};
		bool operator==(const random_access_iterator<T, 2>& it) const {return (this->current == it.getCurrent());};
		bool operator>(const random_access_iterator<T, 2>& it) const {return (this->current < it.getCurrent());};
		bool operator<(const random_access_iterator<T, 2>& it) const {return (this->current > it.getCurrent());};
		bool operator<=(const random_access_iterator<T, 2>& it) const {return (this->current >= it.getCurrent());};
		bool operator>=(const random_access_iterator<T, 2>& it) const {return (this->current <= it.getCurrent());};

		bool operator!=(const random_access_iterator<T, 3>& it) const {return (this->current != it.getCurrent());};
		bool operator==(const random_access_iterator<T, 3>& it) const {return (this->current == it.getCurrent());};
		bool operator>(const random_access_iterator<T, 3>& it) const {return (this->current < it.getCurrent());};
		bool operator<(const random_access_iterator<T, 3>& it) const {return (this->current > it.getCurrent());};
		bool operator<=(const random_access_iterator<T, 3>& it) const {return (this->current >= it.getCurrent());};
		bool operator>=(const random_access_iterator<T, 3>& it) const {return (this->current <= it.getCurrent());};

		random_access_iterator<T, 0> base(){
			return (this->current + 1);
		}
		
		reference operator*(){
			return *this->current;
		}

		pointer	operator->(){
			return this->current;
		}

		rev_random_access_iterator	&operator=(const rev_random_access_iterator &rhs) {
			this->current = rhs.current;
			return *this;
		}

		rev_random_access_iterator &operator++(){
			--this->current;
			return *this;
		}

		rev_random_access_iterator operator++(int){
			rev_random_access_iterator tmp(*this);
			operator++();
			return tmp;
		}

		rev_random_access_iterator &operator--(){
			++this->current;
			return *this;
		}

		rev_random_access_iterator operator--(int){
			rev_random_access_iterator tmp(*this);
			operator--();
			return tmp;
		}

		difference_type operator-(const rev_random_access_iterator &sub){
			return (-(this->current - sub.current));
		}

		rev_random_access_iterator	operator-(difference_type n){
			pointer tmp = this->current;
			for (difference_type i = 0; i < n; i++)
				tmp++;
			return tmp;
		}

		rev_random_access_iterator	operator+(int n){
			pointer tmp = this->current;
			for (difference_type i = 0; i < n; i++)
				tmp--;
			return tmp;
		}

		rev_random_access_iterator	&operator+=(difference_type n){
			for (difference_type i = 0; i < n; i++){
				this->current--;
			}
			return *this;
		}

		rev_random_access_iterator	&operator-=(difference_type n){
			for (difference_type i = 0; i < n; i++){
				this->current++;
			}
			return *this;
		}

		reference	operator[](int n){
			return *(this->current - n);
		}
		friend rev_random_access_iterator operator+(int lhs, rev_random_access_iterator rhs){
			rev_random_access_iterator tmp(rhs);
			tmp += lhs;
			return tmp;
		}
	};
}

#endif