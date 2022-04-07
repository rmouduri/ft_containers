#ifndef REV_CONST_IT_HPP
# define REV_CONST_IT_HPP

#include "random_access_iterator.hpp"

namespace ft{
	template<typename T, int B>
	class rev_const_it : public random_access_iterator<T, B>
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
		
		rev_const_it(){
            this->current = pointer();
        }
		
		rev_const_it(const random_access_iterator<T, 0>& x){
            this->current = (x.getCurrent() - 1);
        }
		rev_const_it(const random_access_iterator<T, 1>& x){
            this->current = (x.getCurrent() - 1);
        }
		rev_const_it(const random_access_iterator<T, 2>& x){
            this->current = x.getCurrent();
        }
		rev_const_it(const random_access_iterator<T, 3>& x){
            this->current = x.getCurrent();
        }

		rev_const_it(const pointer p){
            this->current = p;
			*this += 1;
		}
		
		const_pointer getCurrent() const{
			return (this->current);
		}
		// template<typename U>
		// rev_random_access_iterator(const rev_random_access_iterator<U>& other) : t(other.getT()){
		// 	this->current = const_cast<value_type*>(other.getCurrent());
		// }

		// value_type getT() const {return value_type();}

		// operator rev_random_access_iterator<const value_type>() const {return rev_random_access_iterator<const value_type>(this->current);}

		
		template<int U>
		bool operator!=(const random_access_iterator<T, U>& it) const {return (this->current != it.getCurrent());};
		template<int U>
		bool operator==(const random_access_iterator<T, U>& it) const {return (this->current == it.getCurrent());};
		template<int U>
		bool operator>(const random_access_iterator<T, U>& it) const {return (this->current < it.getCurrent());};
		template<int U>
		bool operator<(const random_access_iterator<T, U>& it) const {return (this->current > it.getCurrent());};
		template<int U>
		bool operator<=(const random_access_iterator<T, U>& it) const {return (this->current >= it.getCurrent());};
		template<int U>
		bool operator>=(const random_access_iterator<T, U>& it) const {return (this->current <= it.getCurrent());};

		rev_const_it base(){
			return this->current;
		}
		
		const_reference operator*() const{
			return *this->current;
		}

		const_pointer	operator->() const{
			return this->current;
		}

		rev_const_it	&operator=(const rev_const_it &rhs) {
			if (this != &rhs)
				this->current = rhs.current;
			return *this;
		}

		rev_const_it &operator++(){
			--this->current;
			return *this;
		}

		rev_const_it operator++(int){
			rev_const_it tmp(*this);
			operator++();
			return tmp;
		}

		rev_const_it &operator--(){
			++this->current;
			return *this;
		}

		rev_const_it operator--(int){
			rev_const_it tmp(*this);
			operator--();
			return tmp;
		}

		difference_type operator-(const rev_const_it &sub){
			return (-(this->current - sub.current));
		}

		rev_const_it	operator-(difference_type n){
			rev_const_it tmp(*this);
			tmp -= n;
			return tmp;
		}

		rev_const_it	operator+(int n){
			rev_const_it tmp(*this);
			tmp += n;
			return tmp;
		}

		rev_const_it	&operator+=(difference_type n){
			for (difference_type i = 0; i < n; i++){
				this->current--;
			}
			return *this;
		}

		rev_const_it	&operator-=(difference_type n){
			for (difference_type i = 0; i < n; i++){
				this->current++;
			}
			return *this;
		}

		reference	operator[](int n){
			return *(this->current - n);
		}
		friend rev_const_it operator+(int lhs, rev_const_it rhs){
			rev_const_it tmp(rhs);
			tmp += lhs;
			return tmp;
		}
	};
}

#endif