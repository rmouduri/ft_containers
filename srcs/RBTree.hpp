#ifndef __RBTREE_HPP__
# define __RBTREE_HPP__

# include <iostream>
# include "vector.hpp"
# include "pair.hpp"
# include "rev_random_access_iterator.hpp"


namespace ft {

	template<class T, class Compare>
	class RBTree {

		class Node {
			public:
			Node *		parent;
			Node *		right;
			Node *		left;
			T			data;
			unsigned	height;

			Node(Node * parent, Node * right = 0, Node * left = 0): parent(parent), right(right), left(left) {}
			Node (const Node & rhs) { *this = rhs; }
			~Node() {}

			Node & operator=(const Node & rhs) {
				if (this != &rhs) {
					this->data = rhs.data;
					this->left = rhs.left;
					this->right = rhs.right;
					this->parent = rhs.parent;
				}
				return *this;
			}

		}; // Node

		template<typename ItT, bool IsConst = false>
		class TreeIterator {
			Node * _current;

			public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef ItT				value_type;
			typedef ItT *			pointer;
			typedef ItT &			reference;
			typedef const ItT &		const_reference;
			typedef std::ptrdiff_t	difference_type;

			typedef TreeIterator<T, false>								iterator;
			typedef TreeIterator<const T, true>							const_iterator;
			// typedef ft::rev_random_access_iterator<iterator>			reverse_iterator;
			// typedef ft::rev_random_access_iterator<const_iterator>		const_reverse_iterator;

			TreeIterator(): _current(0) {}
			explicit TreeIterator(Node * p): _current(p) {}
			TreeIterator(const TreeIterator& other) { *this = other; }
			~TreeIterator() {}

			void* getCurrent(void) const { return _current; }

			// allow conversion from iterator to const_iterator
			operator TreeIterator<const ItT, true>() { return TreeIterator<const ItT, true>(_current); }

			TreeIterator & operator=(const TreeIterator & rhs) {
				if (this != &rhs)
					_current = rhs._current;
				return *this;
			}

			reference operator*(void) { return _current->value; }
			const_reference operator*(void) const { return _current->value; }

			pointer operator->(void) { return &_current->value; }
			const T * operator->(void) const { return &_current->value; }

			// iterator - bidirectional: pre/post increment/decrement {{{

			TreeIterator & operator++(void) {
				if (!_current->right) {
					Node* prev = 0;
					do {
						prev = _current;
						_current = _current->parent;
					} while (_current && _current->right &&
							_current->right == prev);
				}
				else _current = _findInOrderSuccessor(_current->right);

				return *this;
			}

			TreeIterator operator++(int)
			{
				TreeIterator it(*this);

				operator++();

				return it;
			}

			TreeIterator & operator--(void) {
				if (_current->left)
					_current = _findInOrderPredecessor(_current->left);
				else {
					Node* prev = 0;
					do {
						prev = _current;
						_current = _current->parent;
					} while (_current && _current->left && _current->left == prev);
				}

				return *this;
			}

			TreeIterator operator--(int) {
				TreeIterator it(*this);

				operator--();
				return it;
			}


			bool operator!=(TreeIterator<ItT, false> rhs) const { return this->getCurrent() != rhs.getCurrent(); }
			bool operator==(TreeIterator<ItT, false> rhs) const { return this->getCurrent() == rhs.getCurrent(); }

			bool operator==(TreeIterator<const ItT, true> rhs) const { return this->getCurrent() == rhs.getCurrent(); }
			bool operator!=(TreeIterator<const ItT, true> rhs) const { return this->getCurrent() != rhs.getCurrent(); }

		}; // TreeIterator

		private:
			Node *	_root;
			// Node *	_begin;
			// Node *	_end;
			size_t	_size;
			Compare	comp;
			// Alloc		allocator;

		public:
			typedef T			value_type;
			typedef T &			reference;
			typedef const T &	const_reference;
			typedef T *			pointer;
			typedef size_t		size_type;
	
			typedef TreeIterator<T, false>							iterator;
			typedef TreeIterator<const T, true>						const_iterator;
			// typedef ft::rev_random_access_iterator<iterator>		reverse_iterator;
			// typedef ft::rev_random_access_iterator<const_iterator>	const_reverse_iterator;

		RBTree(): _root(0), _size(0), comp() {};
		~RBTree();
		
		Node * allocateNode(const_reference value, Node * parent, Node * left = 0, Node * right = 0) {
			std::allocator<Node> alloc;
			Node * node = alloc.allocate(1);

			alloc.construct(node, Node(value, parent, left, right));
			return node;
		}

		Node * addNode(const T & value, Node * root, Node * parent = 0) {
			if (!root) {
				++this->_size;
				return this->_root = allocateNode(value, parent);
			}

			// if (root == this->_end) {
			// 	root = allocateNode(this->allocator, value, parent, 0, root, 1);
			// 	this->_end->parent = root;
			// 	++this->_size;
			// 	return root;
			// }

			// if (root == this->_begin) {
			// 	Node * p = inserted = allocateNode(this->allocator, value, parent, this->_begin, this->_begin->right);
			// 	this->_begin->parent = p;

			// 	/* if this is the first inserted element, this->_end's parent must be updated too */
			// 	if (this->_begin->right == this->_end) {
			// 		this->_end->parent = p;
			// 		this->_begin->right = 0;
			// 	}
			// 	++this->_size;
			// 	return p;
			// }

			if (comp(value, this->_root->data)) {
				if (!root->left) {
					++this->_size;
					return root->left = allocateNode(value, parent, 0, root);
				}
				else return addNode(value, root->left, root);
			}
			else {// if (comp(this->_root->data, value)) {
				if (!root->right) {
					++this->_size;
					return root->right = allocateNode(value, parent, 0, root);
				}
				else return addNode(value, root->right, root);
			}
		} // addNode

		ft::pair<iterator, bool> insert(const T & val) {
			if (findNode(this->_root, val))
				return ft::pair<iterator, bool>(iterator(), false);
				// return ft::pair<iterator, bool>(this->end(), false);
			return ft::pair<iterator, bool>(iterator(addNode(val, this->_root)), true);
		}

		iterator insert(iterator position, const value_type & val) {
			(void)position;
			return iterator(insert(val));
		}

		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last) {
			while (first != last)
				insert(*first++);
		}

		Node * findNode(Node * root, const T & val) const {
			if (!root)// || root == _begin || root == _end)
				return 0;

			if (this->comp(val, this->_root->data))
				return findNode(root->left, val);
			else if (this->comp(this->_root->data, val))
				return findNode(root->right, val);
			else return root;
		}
	}; // RBTree

} // namespace ft


	// template<typename U>
	// void	swap(U & x, U & y) {
	// 	if (&x == &y)
	// 		return ;
	// 	U tmp = x;
	// 	x = y;
	// 	y = tmp;
	// }

# endif // __RBTREE_HPP__