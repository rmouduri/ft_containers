#ifndef __ENABLE_IF_HPP__
# define __ENABLE_IF_HPP__

namespace ft {
	template<bool B>
	struct enable_if {};

	template<>
	struct enable_if<true>{ typedef int type; };

	template<typename T>
	struct is_integral{ static const bool value = false; };

	template<>
	struct is_integral<bool>{ static const bool value = true; };

	template<>
	struct is_integral<int>{ static const bool value = true; };

	template<>
	struct is_integral<char>{ static const bool value = true; };

	template<>
	struct is_integral<short>{ static const bool value = true; };

	template<>
	struct is_integral<long>{ static const bool value = true; };

	template<>
	struct is_integral<long long>{ static const bool value = true; };

	template<>
	struct is_integral<unsigned char>{ static const bool value = true; };

	template<>
	struct is_integral<unsigned int>{ static const bool value = true; };

	template<>
	struct is_integral<unsigned long>{ static const bool value = true; };

	template<>
	struct is_integral<unsigned long long>{ static const bool value = true; };

	template<>
	struct is_integral<unsigned short>{ static const bool value = false; };
}

#endif // __ENABLE_IF_HPP__