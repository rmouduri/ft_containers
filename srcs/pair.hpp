#ifndef __PAIR_HPP__
# define __PAIR_HPP__

namespace ft {
	
	template <class T1, class T2>
	struct pair {
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type first;
			second_type second;

			pair(void): first(), second() {}

			template<class U, class V>
			pair(const pair<U, V> & rhs): first(rhs.first), second(rhs.second) {}

			pair(const first_type & a, const second_type & b): first(a), second(b) {}

			pair & operator=(const pair & rhs) {
				if (this != &rhs) {
					this->first = rhs.first;
					this->second = rhs.second;
				}
				return *this;
			}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) { return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) { return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) { return rhs<lhs; }

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) { return !(lhs<rhs); }

} // namespace ft


# endif // __PAIR_HPP__