#ifndef CONST_IT_HPP
# define CONST_IT_HPP

#include "random_access_iterator.hpp"

namespace ft
{
	template<typename T, int B>
	class const_it : public random_access_iterator<T, B>
	{
		public:
        	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
		    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type const &	const_reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type const *	const_pointer;
        public:
		const_it() {
            this->current = pointer();
        }

		const_it(pointer p) {
            this->current = p;
		}

		const_it(const random_access_iterator<T, 0>& x) {
            this->current = x.getCurrent();
        }

		const_it(const random_access_iterator<T, 1>& x) {
            this->current = x.getCurrent();
        }

		const_it base(){
			return this->current;
		}
		
		// operator const_it<const T, B>() const {return const_it<const T, B>(this->current);}

		bool operator!=(const random_access_iterator<T, 0>& it) const {return (this->current != it.getCurrent());};
		bool operator==(const random_access_iterator<T, 0>& it) const {return (this->current == it.getCurrent());};
		bool operator>(const random_access_iterator<T, 0>& it) const {return (this->current > it.getCurrent());};
		bool operator<(const random_access_iterator<T, 0>& it) const {return (this->current < it.getCurrent());};
		bool operator<=(const random_access_iterator<T, 0>& it) const {return (this->current <= it.getCurrent());};
		bool operator>=(const random_access_iterator<T, 0>& it) const {return (this->current >= it.getCurrent());};

		bool operator!=(const random_access_iterator<T, 1>& it) const {return (this->current != it.getCurrent());};
		bool operator==(const random_access_iterator<T, 1>& it) const {return (this->current == it.getCurrent());};
		bool operator>(const random_access_iterator<T, 1>& it) const {return (this->current > it.getCurrent());};
		bool operator<(const random_access_iterator<T, 1>& it) const {return (this->current < it.getCurrent());};
		bool operator<=(const random_access_iterator<T, 1>& it) const {return (this->current <= it.getCurrent());};
		bool operator>=(const random_access_iterator<T, 1>& it) const {return (this->current >= it.getCurrent());};


		const_reference operator*() const{
			return *this->current;
		}
        
		const_pointer	operator->() const{
			return this->current;
		}

		const_it	&operator=(const const_it &rhs) {
			this->current = rhs.current;
			return *this;
		}

		const_it &operator++(){
			++this->current;
			return *this;
		}

		const_it operator++(int){
			pointer tmp = this->current++;
			return tmp;
		}

		const_it &operator--(){
			--this->current;
			return *this;
		}

		const_it operator--(int){
			pointer tmp = this->current--;
			return tmp;
		}

		difference_type operator-(const const_it &sub) const{
			difference_type i = 0;
			pointer tmp(this->current);
			while(tmp != sub.current)
			{
				if (tmp > sub.current){
					tmp--;
					i++;
				}
				else{
					tmp++;
					i--;
				}
			}
			return i;
		}

		const_it	operator-(difference_type n) const{
			pointer tmp = this->current;
			for (difference_type i = 0; i < n; i++){
				tmp--;
			}
			return tmp;
		}

		const_it	operator+(difference_type n) const{
			pointer tmp = this->current;
			for (difference_type i = 0; i < n; i++){
				tmp++;
			}
			return tmp;
		}

		const_it	&operator+=(difference_type n){
			for (difference_type i = 0; i < n; i++){
				this->current++;
			}
			return *this;
		}

		const_it	&operator-=(difference_type n){
			for (difference_type i = 0; i < n; i++){
				this->current--;
			}
			return *this;
		}

		const_reference	operator[](int n){
			return this->current[n];
		}
		friend const_it operator+(int lhs, const_it rhs){
			const_it tmp(rhs);
			tmp += lhs;
			return tmp;
		}
	};
}

#endif