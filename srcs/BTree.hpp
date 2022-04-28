#ifndef __RBTREE_HPP__
# define __RBTREE_HPP__

# include <iostream>
# include "pair.hpp"
# include "iterators.hpp"

namespace ft {

	template<class T, class Compare, class Alloc>
	class BTree {

		class Node {
			public:
			T			data;
			Node *		parent;
			Node *		left;
			Node *		right;
			unsigned	height;

			Node(T value, Node * parent, Node * left = 0, Node * right = 0): data(value), parent(parent), left(left), right(right), height(0) {}
			// Node (const Node & rhs) { *this = rhs; }
			~Node() {}

			// Node & operator=(const Node & rhs) {
			// 	if (this != &rhs) {
			// 		this->data = rhs.data;
			// 		this->left = rhs.left;
			// 		this->right = rhs.right;
			// 		this->parent = rhs.parent;
			// 		this->height = rhs.height;
			// 	}
			// 	return *this;
			// }

		}; // Node

		template<typename ItT, int B>
		class TreeIterator {
			protected:
				ItT _current; //ItT = Node *, T = pair<x, y>

			public:
				TreeIterator(): _current(0) {}
				TreeIterator(ItT p): _current(p) {}
				TreeIterator(const TreeIterator & rhs) { *this = rhs; }
				~TreeIterator() {}

				ItT getCurrent(void) const { return this->_current; }

				TreeIterator & operator=(const TreeIterator & rhs) {
					if (this != &rhs)
						_current = rhs._current;
					return *this;
				}

				T & operator*(void) { return _current->data; }
				// const T & operator*(void) const { return _current->data; }

				T * operator->(void) { return &_current->data; }
				const T * operator->(void) const { return &_current->data; }

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

				TreeIterator operator++(int) {
					TreeIterator it(*this);
					operator++();
					return it;
				}

				TreeIterator & operator--(void) {
					// if (!this->_current) {
					// 	iterator();
					// }
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

				bool operator!=(TreeIterator<ItT, 0> rhs) const { return this->getCurrent() != rhs.getCurrent(); }
				bool operator==(TreeIterator<ItT, 0> rhs) const { return this->getCurrent() == rhs.getCurrent(); }

				bool operator==(TreeIterator<ItT, 1> rhs) const { return this->getCurrent() == rhs.getCurrent(); }
				bool operator!=(TreeIterator<ItT, 1> rhs) const { return this->getCurrent() != rhs.getCurrent(); }

		}; // TreeIterator

		template<typename ItT, int B>
		class TreeConstIterator: public TreeIterator<ItT, B> {
			public:
				TreeConstIterator() { this->_current = 0; }
				TreeConstIterator(ItT p) { this->_current = p; }
				TreeConstIterator(const TreeIterator<ItT, 0> & rhs) { this->_current = rhs.getCurrent(); }
				TreeConstIterator(const TreeConstIterator & rhs): TreeIterator<ItT, B>(rhs) { *this = rhs; }
				~TreeConstIterator() {}

				TreeConstIterator & operator=(const TreeConstIterator & rhs) {
					if (this != &rhs)
						this->_current = rhs.getCurrent();
					return *this;
				}

				const ItT getCurrent(void) const { return this->_current; }
				
				const T & operator*(void) const { return this->_current->data; }
				const T * operator->(void) const { return &this->_current->data; }

		};

		template<typename ItT, int B>
		class TreeReverseIterator: public TreeIterator<ItT, B> {
			public:
				TreeReverseIterator() { this->_current = 0; }
				TreeReverseIterator(ItT p) { this->_current = p; }
				TreeReverseIterator(const TreeReverseIterator & rhs): TreeIterator<ItT, B>(rhs) { *this = rhs; }
				TreeReverseIterator(const TreeIterator<ItT, 0> & rhs) { this->_current = rhs.getCurrent(); }
				~TreeReverseIterator() {}

				TreeReverseIterator & operator=(const TreeReverseIterator & rhs) {
					if (this != &rhs)
						this->_current = rhs._current;
					return *this;
				}

				TreeReverseIterator & operator--(void) {
					if (!this->_current->right) {
						Node * prev = 0;
						do {
							prev = this->_current;
							this->_current = this->_current->parent;
						} while (this->_current && this->_current->right && this->_current->right == prev);
					}
					else this->_current = _findInOrderSuccessor(this->_current->right);

					return *this;
				}

				TreeReverseIterator operator--(int) {
					TreeReverseIterator it(*this);
					operator--();
					return it;
				}

				TreeReverseIterator & operator++(void) {
					if (this->_current->left)
						this->_current = _findInOrderPredecessor(this->_current->left);
					else {
						Node * prev = 0;
						do {
							prev = this->_current;
							this->_current = this->_current->parent;
						} while (this->_current && this->_current->left && this->_current->left == prev);
					}

					return *this;
				}

				TreeReverseIterator operator++(int) {
					TreeReverseIterator it(*this);
					operator++();
					return it;
				}

				TreeIterator<ItT, 0> base() { return iterator(this->getCurrent()); }

				bool operator!=(TreeReverseIterator<ItT, 2> rhs) const { return this->getCurrent() != rhs.getCurrent(); }
				bool operator==(TreeReverseIterator<ItT, 2> rhs) const { return this->getCurrent() == rhs.getCurrent(); }

				bool operator==(TreeReverseIterator<ItT, 3> rhs) const { return this->getCurrent() == rhs.getCurrent(); }
				bool operator!=(TreeReverseIterator<ItT, 3> rhs) const { return this->getCurrent() != rhs.getCurrent(); }
		};

		template<typename ItT, int B>
		class TreeConstReverseIterator: public TreeIterator<ItT, B> {
			public:
				TreeConstReverseIterator() { this->_current = 0; }
				TreeConstReverseIterator(ItT p) { this->_current = p; }
				TreeConstReverseIterator(const TreeConstReverseIterator & rhs) { *this = rhs; }
				TreeConstReverseIterator(const TreeReverseIterator<ItT, 2> & rhs) { this->_current = rhs.getCurrent(); }
				TreeConstReverseIterator(const TreeConstIterator<ItT, 1> & rhs) { this->_current = rhs.getCurrent(); }
				TreeConstReverseIterator(const TreeIterator<ItT, 0> & rhs) { this->_current = rhs.getCurrent(); }
				~TreeConstReverseIterator() {}

				TreeConstReverseIterator & operator=(const TreeConstReverseIterator & rhs) {
					if (this != &rhs)
						this->_current = rhs._current;
					return *this;
				}

				const ItT getCurrent(void) const { return this->_current; }
					
				const T & operator*(void) const { return this->_current->data; }
				const T * operator->(void) const { return &this->_current->data; }

				TreeConstReverseIterator & operator--(void) {
					if (!this->_current->right) {
						Node * prev = 0;
						do {
							prev = this->_current;
							this->_current = this->_current->parent;
						} while (this->_current && this->_current->right && this->_current->right == prev);
					}
					else this->_current = _findInOrderSuccessor(this->_current->right);

					return *this;
				}

				TreeConstReverseIterator operator--(int) {
					TreeConstReverseIterator it(*this);
					operator--();
					return it;
				}

				TreeConstReverseIterator & operator++(void) {
					if (this->_current->left)
						this->_current = _findInOrderPredecessor(this->_current->left);
					else {
						Node * prev = 0;
						do {
							prev = this->_current;
							this->_current = this->_current->parent;
						} while (this->_current && this->_current->left && this->_current->left == prev);
					}

					return *this;
				}

				TreeConstReverseIterator operator++(int) {
					TreeConstReverseIterator it(*this);
					operator++();
					return it;
				}

				bool operator!=(TreeIterator<ItT, 2> rhs) const { return this->getCurrent() != rhs.getCurrent(); }
				bool operator==(TreeIterator<ItT, 2> rhs) const { return this->getCurrent() == rhs.getCurrent(); }

				bool operator==(TreeIterator<ItT, 3> rhs) const { return this->getCurrent() == rhs.getCurrent(); }
				bool operator!=(TreeIterator<ItT, 3> rhs) const { return this->getCurrent() != rhs.getCurrent(); }
		};

		// TREE -------------------------------------------------------------------------------------------------------------------------

		typedef typename Alloc::template rebind<Node>::other	NodeAllocator;

		private:
			Node *			_root;
			std::size_t		_size;
			Compare			_comp;
			NodeAllocator	_allocator;

		public:
			typedef T			value_type;
			typedef T &			reference;
			typedef const T &	const_reference;
			typedef T *			pointer;
			typedef size_t		size_type;

	
			typedef TreeIterator<Node *, 0>				iterator;
			typedef TreeConstIterator<Node *, 1>		const_iterator;
			typedef TreeReverseIterator<Node *, 2>		reverse_iterator;
			typedef TreeConstReverseIterator<Node *, 3>	const_reverse_iterator;

		BTree(): _root(0), _size(0), _comp(), _allocator() {}
		~BTree() {}

		Node * getData() { return this->_root; }

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

			if (_comp(value.first, root->data.first)) {
				// std::cout << value.first << " less than " << root->data.first << '\n';
				if (!root->left) {
					++this->_size;
					return root->left = allocateNode(value, root, 0, 0);
				}
				else return addNode(value, root->left, root);
			}
			else {// if (_comp(root->data, value)) {
				// std::cout << value.first << " bigger than " << root->data.first << '\n';
				if (!root->right) {
					++this->_size;
					return root->right = allocateNode(value, root, 0, 0);
				}
				else return addNode(value, root->right, root);
			}
		} // addNode

		ft::pair<iterator, bool> insert(const T & val) {
			Node * insertedNode = findNode(this->_root, val);
			if (insertedNode)
				return ft::pair<iterator, bool>(iterator(insertedNode), false);
			// std::cout << "adding node " << val.first << ":\n";
			insertedNode = addNode(val, this->_root);
			// print2D();
			// std::cout << "balancing:\n";
			this->_root = _rebalanceTree(insertedNode);
			// print2D();
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

			if (this->_comp(val.first, root->data.first))
				return findNode(root->left, val);
			else if (this->_comp(root->data.first, val.first))
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

		unsigned __computeNodeHeight(Node * node) const {
			unsigned hl, hr;

			hl = node->left ? node->left->height : 0;
			hr = node->right ? node->right->height : 0;

			return hl >= hr ? hl + 1 : hr + 1;
		}

		int __computeBalanceFactor(Node * node) {
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
			p->height = __computeNodeHeight(p);
			pl->height = __computeNodeHeight(pl);

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

			pl->height = __computeNodeHeight(pl);
			p->height = __computeNodeHeight(p);
			plr->height = __computeNodeHeight(plr);

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
			p->height = __computeNodeHeight(p);
			pr->height = __computeNodeHeight(pr);

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

			pr->height = __computeNodeHeight(pr);
			p->height = __computeNodeHeight(p);
			prl->height = __computeNodeHeight(prl);

			if (_root == p) {
				_root = prl;
			}

			return prl;
		}

		Node * _rebalanceTree(Node * & root) {
			Node * tmp = root;

			while (tmp) {
				tmp->height = __computeNodeHeight(tmp);
				// std::cout << "rebalance: " << tmp->data.first << ' ' << tmp->data.second << ' ';

				int bf = __computeBalanceFactor(tmp), bf2 = 0;

				// std::cout << "bf: " << bf << '\n';
				if (bf == 2) {
					bf2 = __computeBalanceFactor(tmp->left);
					if (bf2 == 1) {
						// std::cout << "LL_rotate\n";
						LL_rotate(tmp);
					} else if (bf2 == -1) {
						// std::cout << "LR_rotate\n";
						LR_rotate(tmp);
					}

				}
				else if (bf == -2) {
					bf2 = __computeBalanceFactor(tmp->right);
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

			while (tmp && tmp->left)
				tmp = tmp->left;
			return iterator(tmp);
		}

		const_iterator begin() const {
			Node * tmp = this->_root;

			while (tmp && tmp->left)
				tmp = tmp->left;
			return const_iterator(tmp);
		}

		iterator end() { return iterator(); }
		const_iterator end() const { return const_iterator(); }

		reverse_iterator rbegin() {
			Node * tmp = this->_root;

			while (tmp && tmp->right)
				tmp = tmp->right;
			return reverse_iterator(tmp);
		}

		const_reverse_iterator rbegin() const {
			Node * tmp = this->_root;

			while (tmp && tmp->right)
				tmp = tmp->right;
			return const_reverse_iterator(tmp);
		}

		reverse_iterator rend() { return reverse_iterator(); }
		const_reverse_iterator rend() const { return const_reverse_iterator(); }


		size_type getSize() const { return this->_size; }

		size_type getMaxSize() const { return this->_allocator.max_size(); }


	}; // BTree

} // namespace ft

# endif // __RBTREE_HPP__