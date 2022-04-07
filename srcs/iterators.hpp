#ifndef ITERATOR_TRAITS_H_
#define ITERATOR_TRAITS_H_

#include <cstddef>
#include <iterator>

namespace ft{
template <class _Iterator>
struct iterator_traits {
  typedef typename _Iterator::iterator_category iterator_category;
  typedef typename _Iterator::value_type value_type;
  typedef typename _Iterator::difference_type difference_type;
  typedef typename _Iterator::pointer pointer;
  typedef typename _Iterator::reference reference;
};

class random_access_iterator_tag{};

template <class T>
struct iterator_traits<T*> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T*  pointer;
  typedef T&  reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*>{
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T*  pointer;
  typedef const T&  reference;
  typedef ft::random_access_iterator_tag iterator_category;
  };

  template <class Category, class T, class Distance = ptrdiff_t,
    class Pointer = T*, class Reference = T&>
    class iterator
    {
         public:
                typedef T           value_type;
                typedef Distance    difference_type;
                typedef Pointer     pointer;
                typedef Reference   reference;
                typedef Category    iterator_category;
        };
}
#endif