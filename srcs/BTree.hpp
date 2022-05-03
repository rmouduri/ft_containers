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
			T				data;
			Node *			parent;
			Node *			left;
			Node *			right;
			unsigned int	height;

			Node(): data(T()), parent(0), left(0), right(0), height(0) {}
			Node(T value, Node * parent, Node * left = 0, Node * right = 0, unsigned int height = 0): data(value), parent(parent), left(left), right(right), height(height) {}
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
			// protected:
			public:
				ItT _current; //ItT = Node * , T = pair<x, y>
				ItT _root;

				ItT getCurrent(void) const { return this->_current; }
				ItT getRoot(void) const { return this->_root; }

			public:
				TreeIterator(): _current(0), _root(0) {}
				TreeIterator(ItT current, ItT root): _current(current), _root(root) {}
				TreeIterator(const TreeIterator & rhs) { *this = rhs; }
				~TreeIterator() {}


				TreeIterator & operator=(const TreeIterator & rhs) {
					if (this != &rhs) {
						_current = rhs.getCurrent();
						_root =rhs.getRoot();
					}
					return *this;
				}

				T & operator*(void) { return _current->data; }
				// const T & operator*(void) const { return _current->data; }

				T * operator->(void) { return &_current->data; }
				const T * operator->(void) const { return &_current->data; }

				TreeIterator & operator++(void) {
					// if (!this->_current) {
					// 	this->_current = _getFirst(_root, _begin);
					// 	return *this;
					// }
					if (!_current->right) {
						Node * prev = 0;
						do {
							prev = _current;
							_current = _current->parent;
						} while (_current && _current->right && _current->right == prev);
					}
					else _current = _goMaxLeft(_current->right);

					return *this;
				}

				TreeIterator operator++(int) {
					TreeIterator it(*this);
					operator++();
					return it;
				}

				TreeIterator & operator--(void) {
					// if (!this->_current) {
					// 	this->_current = _getLast(_root);
					// 	return *this;
					// }
					if (_current->left)
						_current = _goMaxRight(_current->left);
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
			// protected:
			public:
				const ItT getCurrent(void) const { return this->_current; }

			public:
				TreeConstIterator() { this->_current = 0; this->_root = 0; }
				TreeConstIterator(ItT current, ItT root) { this->_current = current; this->_root = root; }
				TreeConstIterator(const TreeIterator<ItT, 0> & rhs) { this->_current = rhs.getCurrent(); this->_root = rhs.getRoot(); }
				TreeConstIterator(const TreeConstIterator & rhs): TreeIterator<ItT, B>(rhs) { *this = rhs; }
				~TreeConstIterator() {}

				TreeConstIterator & operator=(const TreeConstIterator & rhs) {
					if (this != &rhs) {
						this->_current = rhs.getCurrent();
						this->_root = rhs.getRoot();
					}
					return *this;
				}

				const T & operator*(void) const { return this->_current->data; }
				const T * operator->(void) const { return &this->_current->data; }

		};

		template<typename ItT, int B>
		class TreeReverseIterator: public TreeIterator<ItT, B> {
			public:
				TreeReverseIterator() { this->_current = 0; this->_root = 0; }
				TreeReverseIterator(ItT current, ItT root) { this->_current = current; this->_root = root; }
				TreeReverseIterator(const TreeReverseIterator & rhs): TreeIterator<ItT, B>(rhs) { *this = rhs; }
				TreeReverseIterator(const TreeIterator<ItT, 0> & rhs) { this->_current = rhs.getCurrent(); this->_root = rhs.getRoot(); }
				~TreeReverseIterator() {}

				TreeReverseIterator & operator=(const TreeReverseIterator & rhs) {
					if (this != &rhs) {
						this->_current = rhs.getCurrent();
						this->_root = rhs.getRoot();
					}
					return *this;
				}

				T & operator*(void) const {
					if (this->_current->left)
						return _goMaxRight(this->_current->left)->data;
					ItT tmp = this->_current;
					ItT prev = 0;
					do {
						prev = tmp;
						tmp = tmp->parent;
					} while (tmp && tmp->left && tmp->left == prev);
					return tmp->data;
				}

				T * operator->(void) const { 
					return &this->operator*();
				 }

				TreeReverseIterator & operator--(void) {
					if (this->_current->right) 
						this->_current = _goMaxLeft(this->_current->right);
					else {
						Node * prev = 0;
						do {
							prev = this->_current;
							this->_current = this->_current->parent;
						} while (this->_current && this->_current->right && this->_current->right == prev);
					}

					return *this;
				}

				TreeReverseIterator operator--(int) {
					TreeReverseIterator it(*this);
					// std::cout << "sss: " << it->first << ' ' << it->second << std::endl;
					this->operator--();
					// std::cout << "sss: " << it->first << ' ' << it->second << std::endl;
					return it;
				}

				TreeReverseIterator & operator++(void) {
					if (this->_current->left)
						this->_current = _goMaxRight(this->_current->left);
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
					// std::cout << "sss: " << it->first << ' ' << it->second << std::endl;
					this->operator++();
					// std::cout << "sss: " << it->first << ' ' << it->second << std::endl;
					return it;
				}

				TreeIterator<ItT, 0> base() const { return TreeIterator<ItT, 0>(this->getCurrent(), this->getRoot()); }

				bool operator!=(TreeReverseIterator<ItT, 2> rhs) const { return this->base() != rhs.base(); }
				bool operator==(TreeReverseIterator<ItT, 2> rhs) const { return this->base() == rhs.base(); }

				bool operator==(TreeReverseIterator<ItT, 3> rhs) const { return this->base() == rhs.base(); }
				bool operator!=(TreeReverseIterator<ItT, 3> rhs) const { return this->base() != rhs.base(); }
		};

		template<typename ItT, int B>
		class TreeConstReverseIterator: public TreeIterator<ItT, B> {
			// protected:
			public:
				const ItT getCurrent(void) const { return this->_current; }

			public:
				TreeConstReverseIterator() { this->_current = 0; this->_root = 0; }
				TreeConstReverseIterator(ItT current, ItT root) { this->_current = current; this->_root = root; }
				TreeConstReverseIterator(const TreeConstReverseIterator & rhs): TreeIterator<ItT, B>(rhs) { *this = rhs; }
				TreeConstReverseIterator(const TreeReverseIterator<ItT, 2> & rhs) { this->_current = rhs.getCurrent(); this->_root = rhs.getRoot(); }
				TreeConstReverseIterator(const TreeConstIterator<ItT, 1> & rhs) { this->_current = rhs.getCurrent(); this->_root = rhs.getRoot(); }
				TreeConstReverseIterator(const TreeIterator<ItT, 0> & rhs) { this->_current = rhs.getCurrent(); this->_root = rhs.getRoot(); }
				~TreeConstReverseIterator() {}

				TreeConstReverseIterator & operator=(const TreeConstReverseIterator & rhs) {
					if (this != &rhs) {
						this->_current = rhs.getCurrent();
						this->_root = rhs.getRoot();
					}
					return *this;
				}

				const T & operator*(void) const {
					if (this->_current && this->_current->left)
						return _goMaxRight(this->_current->left)->data;
					ItT tmp = this->_current;
					ItT prev = 0;
					do {
						prev = tmp;
						tmp = tmp->parent;
					} while (tmp && tmp->left && tmp->left == prev);
					return tmp->data;
				}

				const T * operator->(void) const { 
					return &this->operator*();
				 }

				TreeConstReverseIterator & operator--(void) {
					if (!this->_current->right) {
						Node * prev = 0;
						do {
							prev = this->_current;
							this->_current = this->_current->parent;
						} while (this->_current && this->_current->right && this->_current->right == prev);
					}
					else this->_current = _goMaxLeft(this->_current->right);

					return *this;
				}

				TreeConstReverseIterator operator--(int) {
					TreeConstReverseIterator it(*this);
					// std::cout << "sss: " << it->first << ' ' << it->second << std::endl;
					this->operator--();
					// std::cout << "sss: " << it->first << ' ' << it->second << std::endl;
					return it;
				}

				TreeConstReverseIterator & operator++(void) {
					if (this->_current->left)
						this->_current = _goMaxRight(this->_current->left);
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
					// std::cout << "sss: " << it->first << ' ' << it->second << std::endl;
					this->operator++();
					// std::cout << "sss: " << it->first << ' ' << it->second << std::endl;
					return it;
				}

				// TreeIterator<ItT, 1> base() const { return TreeConstIterator<ItT, 0>(this->getCurrent(), this->getRoot()); }

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
			Node *			_begin;
			Node *			_end;

		public:
			typedef T			value_type;
			typedef T &			reference;
			typedef const T &	const_reference;
			typedef T *			pointer;
			typedef size_t		size_type;

	
			typedef TreeIterator<Node * , 0>				iterator;
			typedef TreeConstIterator<Node * , 1>		const_iterator;
			typedef TreeReverseIterator<Node * , 2>		reverse_iterator;
			typedef TreeConstReverseIterator<Node * , 3>	const_reverse_iterator;

		BTree(): _root(0), _size(0), _comp(), _allocator(), _begin(allocateNode(T(), 0)), _end(allocateNode(T(), 0)) {}
		~BTree() {}

		Node * _getRoot() const { return this->_root; }

		static Node * allocateNode(const_reference value, Node * parent, Node * left = 0, Node * right = 0) {
			std::allocator<Node> alloc;
			Node * node = alloc.allocate(1);

			alloc.construct(node, Node(value, parent, left, right));
			return node;
		}

		Node * addNode(const T & value, Node * & root, Node * parent = 0) {
			if (!root) {
				++this->_size;
				this->_root = allocateNode(value, parent, _begin, _end);
				_begin->parent = this->_root;
				_end->parent = this->_root;
				return this->_root;
			}

			if (_comp(value.first, root->data.first)) {
				// std::cout << value.first << " less than " << root->data.first << '\n';
				if (root->left == _begin || !root->left) {
					++this->_size;
					if (root->left == _begin) {
						root->left = allocateNode(value, root, _begin, 0);
						_begin->parent = root->left;
						return root->left;
					}
					else return root->left = allocateNode(value, root, 0, 0);
				}
				else return addNode(value, root->left, root);
			}
			else {// if (_comp(root->data, value)) {
				// std::cout << value.first << " bigger than " << root->data.first << '\n';
				if (root->right == _end || !root->right) {
					++this->_size;
					if (root->right == _end) {
						root->right = allocateNode(value, root, 0, _end);
						_end->parent = root->right;
						return root->right;
					}
					else return root->right = allocateNode(value, root, 0, 0);
				}
				else return addNode(value, root->right, root);
			}
		} // addNode

		ft::pair<iterator, bool> insert(const T & val) {
			Node * insertedNode = findNode(this->_root, val);
			if (insertedNode && insertedNode != _end)
				return ft::pair<iterator, bool>(iterator(insertedNode, _root), false);

			#ifdef DEBUG
				std::cout << "adding node " << val.first << ':' << std::endl;
			#endif
			insertedNode = addNode(val, this->_root);
			#ifdef DEBUG
				print2D();
				std::cout << "balancing:" << std::endl;
			#endif
			this->_root = rebalanceTree(insertedNode);
			#ifdef DEBUG
				print2D();
			#endif

			return ft::pair<iterator, bool>(iterator(insertedNode, _root), true);
		}

		iterator insert(iterator position, const value_type & val) {
			(void)position;
			return insert(val).first;
		}

		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last) {
			while (first != last) {
				insert(*first);
				++first;
			}
		}

		Node * findNode(Node * root, const T & val) const {
			if (!root || root == _begin || root == _end) {
				return _end;
			}

			if (this->_comp(val.first, root->data.first))
				return findNode(root->left, val);
			else if (this->_comp(root->data.first, val.first))
				return findNode(root->right, val);
			else return root;
		}

		static Node * _goMaxRight(Node * p) {
			while (p && p->right)
				p = p->right;
			return p;
		}

		static Node * _goMaxLeft(Node * p) {
			while (p && p->left)
				p = p->left;
			return p;
		}

		static Node * _getFirst(Node * root, Node * _begin) {
			while (root && root->parent)
				root = root->parent;
			while (root && root->left && root->left != _begin)
				root = root->left;
			return root;
		}

		static Node * _getLast(Node * root, Node * _end) {
			while (root && root->parent)
				root = root->parent;
			while (root && root->right && root->right != _end)
				root = root->right;
			return root;
		}

		int getNodeHeight(Node * node) const {
			int hl, hr;

			hl = node->left && node->left != this->_begin ? node->left->height : 0;
			hr = node->right && node->right != this->_end ? node->right->height : 0;

			return hl >= hr ? hl + 1 : hr + 1;
		}

		int getBF(Node * node) {
			int hl, hr;

			hl = node->left && node->left != this->_begin ? node->left->height : 0;
			hr = node->right && node->right != this->_end ? node->right->height : 0;

			return hl - hr;
		}

		void LLRotate(Node * p){
			Node * pl = p->left;
			Node * plr = pl->right;

			if (p == _root)
				_root = pl;
			if (p->parent) {
				if (p->parent->right == p)
					p->parent->right = pl;
				else p->parent->left = pl;
			}
			pl->parent = p->parent;
			pl->right = p;

			p->parent = pl;
			p->left = plr;

			if (plr)
				plr->parent = p;
		}

		void LRRotate(Node * p) {
			Node * pl = p->left;
			Node * plr = pl->right;

			if (p == _root)
				_root = plr;
			if (p->parent) {
				if (p->parent->right == p)
					p->parent->right = plr;
				else p->parent->left = plr;
			}

			plr->parent = p->parent;
			plr->left = pl;
			plr->right = p;

			p->parent = plr;
			pl->parent = plr;

			p->left = plr->right;
			if (plr->right)
				plr->right->parent = p;

			pl->right = plr->left;
			if (plr->left)
				plr->left->parent = pl;
		}

		void RRRotate(Node * p) {
			Node * pr = p->right;
			Node * prl = pr->left;

			if (p == _root)
				_root = pr;
			if (p->parent) {
				if (p->parent->right == p)
					p->parent->right = pr;
				else p->parent->left = pr;
			}

			pr->parent = p->parent;
			pr->left = p;

			p->parent = pr;
			p->right = prl;

			if (prl)
				prl->parent = p;
		}

		void RLRotate(Node * p) {
			Node * pr = p->right;
			Node * prl = pr->left;

			if (p == _root)
				_root = prl;
			if (p->parent) {
				if (p->parent->right == p)
					p->parent->right = prl;
				else p->parent->left = prl;
			}

			prl->parent = p->parent;
			prl->left = p;
			prl->right = pr;

			p->parent = prl;
			pr->parent = prl;

			p->right = prl->left;
			if (prl->left) {
				prl->left->parent = p;
			}

			pr->left = prl->right;
			if (prl->right) {
				prl->right->parent = pr;
			}
		}

		Node * rebalanceTree(Node * root) {
			Node * tmp = root;

			while (tmp) {
				tmp->height = getNodeHeight(tmp);
				// std::cout << "rebalance: " << tmp->data.first << ' ' << tmp->data.second << ' ';

				int bf = getBF(tmp), bf2 = 0;

				// std::cout << "bf: " << bf << '\n';
				if (bf == 2) {
					bf2 = getBF(tmp->left);
					if (bf2 == 1) {
						#ifdef DEBUG
							std::cout << "node '" << tmp->data.first << "': LLRotate\n";
						#endif
						LLRotate(tmp);
					} else if (bf2 == -1) {
						#ifdef DEBUG
							std::cout << "node '" << tmp->data.first << "': LRRotate\n";
						#endif
						LRRotate(tmp);
					}

				}
				else if (bf == -2) {
					bf2 = getBF(tmp->right);
					if (bf2 == 1) {
						#ifdef DEBUG
							std::cout << "node '" << tmp->data.first << "': RLRotate\n";
						#endif
						RLRotate(tmp);
					}
					if (bf2 == -1) {
						#ifdef DEBUG
							std::cout << "node '" << tmp->data.first << "': RRRotate\n";
						#endif
						RRRotate(tmp);
					}
				}
				if (tmp->parent)
					tmp = tmp->parent;
				else
					break ;
			}

			return tmp;
		}

		void print2DUtil(Node * root, int space) {
			if (root == NULL)
				return;
		
			space += 6;
		
			print2DUtil(root->right, space);

			std::cout << std::endl;
			for (int i = 6; i < space; i++)
				std::cout << " ";
			std::cout << '\'' << root->data.first << '\'' << std::endl;
		
			print2DUtil(root->left, space);
		}
		
		void print2D() { print2DUtil(this->_root, 0); }

		iterator begin() {
			Node * tmp = this->_root;

			while (tmp && tmp->left && tmp->left != _begin)
				tmp = tmp->left;
			return iterator(tmp, _root);
		}

		const_iterator begin() const {
			Node * tmp = this->_root;

			while (tmp && tmp->left && tmp->left != _begin)
				tmp = tmp->left;
			return const_iterator(tmp, _root);
		}

		iterator end() { return iterator(_end, _root); }
		const_iterator end() const { return const_iterator(_end, _root); }

		reverse_iterator rbegin() { return reverse_iterator(_end, _root); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_end, _root); }

		reverse_iterator rend() { return reverse_iterator(_getFirst(_root, _begin), _root); }
		const_reverse_iterator rend() const { return const_reverse_iterator(getBF(_root, _begin), _root); }

		size_type getSize() const { return this->_size; }

		size_type getMaxSize() const { return this->_allocator.max_size(); }


	}; // BTree

} // namespace ft

# endif // __RBTREE_HPP__