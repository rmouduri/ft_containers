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
			T			data;
			Node *		parent;
			Node *		left;
			Node *		right;
			unsigned	height;

			Node(T value, Node * parent, Node * left = 0, Node * right = 0): data(value), parent(parent), left(left), right(right), height(0) {}
			Node (const Node & rhs) { *this = rhs; }
			~Node() {}

			Node & operator=(const Node & rhs) {
				if (this != &rhs) {
					this->data = rhs.data;
					this->left = rhs.left;
					this->right = rhs.right;
					this->parent = rhs.parent;
					this->height = rhs.height;
				}
				return *this;
			}

		}; // Node

		template<typename ItT, bool IsConst = false>
		class TreeIterator {
			Node * _current;

			public:
			typedef ItT				value_type;
			typedef ItT *			pointer;
			typedef ItT &			reference;
			typedef const ItT &		const_reference;

			TreeIterator(): _current(0) {}
			TreeIterator(Node * p): _current(p) {}
			TreeIterator(const TreeIterator & other) { *this = other; }
			~TreeIterator() {}

			Node * getCurrent(void) const { return _current; }

			TreeIterator & operator=(const TreeIterator & rhs) {
				if (this != &rhs)
					_current = rhs._current;
				return *this;
			}

			reference operator*(void) { return _current->data; }
			const_reference operator*(void) const { return _current->data; }

			T * operator->(void) { return &_current->data; }
			const T * operator->(void) const { return &_current->data; }

			// iterator - bidirectional: pre/post increment/decrement {{{

			TreeIterator & operator++(void) {
				if (!_current->right) {
					Node * prev = 0;
					do {
						prev = _current;
						_current = _current->parent;
					} while (_current && _current->right && _current->right == prev);
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
					Node * prev = 0;
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


		template<typename ItT, bool IsConst = false>
		class TreeConstIterator {
			Node * _current;

			public:
			typedef ItT				value_type;
			typedef ItT *			pointer;
			typedef ItT &			reference;
			typedef const ItT &		const_reference;

			TreeConstIterator(): _current(0) {}
			TreeConstIterator(Node * p): _current(p) {}
			TreeConstIterator(const TreeIterator<T, false> & other): _current(other.getCurrent()) {}
			TreeConstIterator(const TreeConstIterator & other) { *this = other; }
			~TreeConstIterator() {}

			Node * getCurrent(void) const { return _current; }

			TreeConstIterator & operator=(const TreeConstIterator & rhs) {
				if (this != &rhs)
					_current = rhs._current;
				return *this;
			}

			reference operator*(void) { return _current->data; }
			const_reference operator*(void) const { return _current->data; }

			T * operator->(void) { return &_current->data; }
			const T * operator->(void) const { return &_current->data; }

			// iterator - bidirectional: pre/post increment/decrement {{{

			TreeConstIterator & operator++(void) {
				if (!_current->right) {
					Node * prev = 0;
					do {
						prev = _current;
						_current = _current->parent;
					} while (_current && _current->right && _current->right == prev);
				}
				else _current = _findInOrderSuccessor(_current->right);

				return *this;
			}

			TreeConstIterator operator++(int)
			{
				TreeConstIterator it(*this);

				operator++();

				return it;
			}

			TreeConstIterator & operator--(void) {
				if (_current->left)
					_current = _findInOrderPredecessor(_current->left);
				else {
					Node * prev = 0;
					do {
						prev = _current;
						_current = _current->parent;
					} while (_current && _current->left && _current->left == prev);
				}

				return *this;
			}

			TreeConstIterator operator--(int) {
				TreeConstIterator it(*this);

				operator--();
				return it;
			}

			bool operator!=(TreeConstIterator<ItT, false> rhs) const { return this->getCurrent() != rhs.getCurrent(); }
			bool operator==(TreeConstIterator<ItT, false> rhs) const { return this->getCurrent() == rhs.getCurrent(); }

			bool operator==(TreeConstIterator<const ItT, true> rhs) const { return this->getCurrent() == rhs.getCurrent(); }
			bool operator!=(TreeConstIterator<const ItT, true> rhs) const { return this->getCurrent() != rhs.getCurrent(); }

		}; // TreeConstIterator

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
	
			typedef TreeIterator<Node *, false>							iterator;
			typedef TreeConstIterator<const Node *, true>				const_iterator;
			// typedef ft::rev_random_access_iterator<iterator>		reverse_iterator;
			// typedef ft::rev_random_access_iterator<const_iterator>	const_reverse_iterator;

		RBTree(): _root(0), _size(0), comp() {}
		~RBTree() {}

		Node * getData() {return this->_root;}

		Node * allocateNode(const_reference value, Node * parent, Node * left = 0, Node * right = 0) {
			std::allocator<Node> alloc;
			Node * node = alloc.allocate(1);

			alloc.construct(node, Node(value, parent, left, right));
			return node;
		}

		Node * addNode(const T & value, Node * & root, Node * parent = 0) {
			if (!root) {
				++this->_size;
				return this->_root = allocateNode(value, parent);
			}

			if (comp(value.first, root->data.first)) {
				// std::cout << value.first << " less than " << root->data.first << '\n';
				if (!root->left) {
					++this->_size;
					return root->left = allocateNode(value, root, 0, 0);
				}
				else return addNode(value, root->left, root);
			}
			else {// if (comp(root->data, value)) {
				// std::cout << value.first << " bigger than " << root->data.first << '\n';
				if (!root->right) {
					++this->_size;
					return root->right = allocateNode(value, root, 0, 0);
				}
				else return addNode(value, root->right, root);
			}
		} // addNode

		ft::pair<iterator, bool> insert(const T & val) {
			if (findNode(this->_root, val))
				return ft::pair<iterator, bool>(iterator(), false);
			std::cout << "adding node " << val.first << ":\n";
			Node * insertedNode = addNode(val, this->_root);
			print2D();
			std::cout << "balancing:\n";
			this->_root = _rebalanceTree(insertedNode);
			print2D();
			return ft::pair<iterator, bool>(iterator(insertedNode), true);
		}

		iterator insert(iterator position, const value_type & val) {
			(void)position;
			return insert(val).first;
		}

		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last) {
			while (first != last)
				insert(*first++);
		}

		Node * findNode(Node * root, const T & val) const {
			if (!root) {
				return 0;
			}

			if (this->comp(val.first, root->data.first))
				return findNode(root->left, val);
			else if (this->comp(root->data.first, val.first))
				return findNode(root->right, val);
			else return root;
		}

		static Node * _findInOrderPredecessor(Node * p) {
			while (p && p->right && p->right)
				p = p->right;
			return p;
		}

		static Node * _findInOrderSuccessor(Node * p) {
			while (p && p->left && p->left)
				p = p->left;
			return p;
		}

		unsigned _computeNodeHeight(Node * node) const {
			unsigned hl, hr;

			hl = node->left ? node->left->height : 0;
			hr = node->right ? node->right->height : 0;

			return hl >= hr ? hl + 1 : hr + 1;
		}

		int _computeBalanceFactor(Node * node) {
			unsigned hl, hr;

			hl = node->left ? node->left->height : 0;
			hr = node->right ? node->right->height : 0;

			return hl - hr;
		}

		Node* LL_rotate(Node* p){
			Node *pl = p->left, *plr = pl->right;

			pl->right = p;
			p->left = plr;
			if (plr) {
				plr->parent = p;
			}
			pl->parent = p->parent;
			p->parent = pl;
			p->height = _computeNodeHeight(p);
			pl->height = _computeNodeHeight(pl);

			if (_root == p) {
				_root = pl;
			}

			if (pl->parent) {
				if (pl->parent->right == pl->right)
					pl->parent->right = pl;
				else
					pl->parent->left = pl;
			}
			return pl;
		}

		Node* LR_rotate(Node* p) {
			Node *pl = p->left, *plr = pl->right;

			pl->right = plr->left;
			if (plr->left) {
				plr->left->parent = pl;
			}

			p->left = plr->right;
			if (plr->right) {
				plr->right->parent = p;
			}

			plr->right = p;
			plr->parent = p->parent;
			p->parent = plr;
			plr->left = pl;
			pl->parent = plr;

			pl->height = _computeNodeHeight(pl);
			p->height = _computeNodeHeight(p);
			plr->height = _computeNodeHeight(plr);

			if (_root == p) {
				_root = plr;
			}

			return plr;
		}

		Node* RR_rotate(Node* p) {
			Node *pr = p->right, *prl = pr->left;

			pr->left = p;
			p->right = prl;
			if (prl) {
				prl->parent = p;
			}
			pr->parent = p->parent;
			p->parent = pr;
			p->height = _computeNodeHeight(p);
			pr->height = _computeNodeHeight(pr);

			if (_root == p) {
				_root = pr;
			}
			if (pr->parent) {
				if (pr->parent->left == pr->left)
					pr->parent->left = pr;
				else
					pr->parent->right = pr;
			}
			return pr;
		}

		Node * RL_rotate(Node* p) {
			Node *pr = p->right, *prl = pr->left;

			pr->left = prl->right;
			if (prl->right) {
				prl->right->parent = pr;
			}

			p->right = prl->left;
			if (prl->left) {
				prl->left->parent = p;
			}

			prl->left = p;
			prl->parent = p->parent;
			p->parent = prl;
			prl->right = pr;
			pr->parent = prl;

			pr->height = _computeNodeHeight(pr);
			p->height = _computeNodeHeight(p);
			prl->height = _computeNodeHeight(prl);

			if (_root == p) {
				_root = prl;
			}

			return prl;
		}

		Node * _rebalanceTree(Node * & root) {
			Node * tmp = root;

			while (tmp) {
				tmp->height = _computeNodeHeight(tmp);
				// std::cout << "rebalance: " << tmp->data.first << ' ' << tmp->data.second << ' ';

				int bf = _computeBalanceFactor(tmp), bf2 = 0;

				// std::cout << "bf: " << bf << '\n';
				if (bf == 2) {
					bf2 = _computeBalanceFactor(tmp->left);
					if (bf2 == 1) {
						// std::cout << "LL_rotate\n";
						LL_rotate(tmp);
					} else if (bf2 == -1) {
						// std::cout << "LR_rotate\n";
						LR_rotate(tmp);
					}

				}
				else if (bf == -2) {
					bf2 = _computeBalanceFactor(tmp->right);
					if (bf2 == 1) {
						// std::cout << "RL_rotate\n";
						RL_rotate(tmp);
					}
					if (bf2 == -1) {
						// std::cout << "RR_rotate\n";
						RR_rotate(tmp);
					}
				}
				if (tmp->parent)
					tmp = tmp->parent;
				else
					break ;
			}

			return tmp;
		}

		void _printInOrder(Node * root) const {
			if (root->left) {
				_printInOrder(root->left);
			}
				std::cout << root->data.first << "\n";
			if (root->right) {
				_printInOrder(root->right);
			}
		}

		void print2DUtil(Node *root, int space) {
			if (root == NULL)
				return;
		
			space += 6;
		
			print2DUtil(root->right, space);
		
			std::cout << std::endl;
			for (int i = 6; i < space; i++)
				std::cout << " ";
			std::cout << root->data.first << "\n";
		
			print2DUtil(root->left, space);
		}
		
		void print2D() { print2DUtil(this->_root, 0); }

		iterator begin() {
			Node * tmp = this->_root;

			while (tmp->left)
				tmp = tmp->left;
			return iterator(tmp);
		}

		const_iterator begin() const {
			Node * tmp = this->_root;

			while (tmp->left)
				tmp = tmp->left;
			return const_iterator(tmp);
		}

		iterator end() { return iterator(); }
		iterator end() const { return const_iterator(); }

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