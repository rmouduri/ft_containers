#ifndef __RBTREE_HPP__
# define __RBTREE_HPP__

# include <iostream>
# include "pair.hpp"
# include "iterators.hpp"
# include "equal.hpp"

namespace ft {

	template<class T, class Compare, class Alloc>
	class BTree {

		class Node {
			public:
			T				data;
			Node *			parent;
			Node *			left;
			Node *			right;
			int				height;

			Node(): data(T()), parent(0), left(0), right(0), height(0) {}
			Node(T value, Node * parent, Node * left = 0, Node * right = 0, int height = 0): data(value), parent(parent), left(left), right(right), height(height) {}
			~Node() {}

			void swap(Node & rhs) {
				Node * leftTmp = left;
				Node * rightTmp = right;

				left = rhs.left == this ? &rhs : rhs.left;
				right = rhs.right == this ? &rhs : rhs.right;
				if (left)
					left->parent = this;
				if (right)
					right->parent = this;

				rhs.left = leftTmp == &rhs ? this : leftTmp;
				rhs.right = rightTmp == &rhs ? this : rightTmp;
				if (leftTmp)
					leftTmp->parent = &rhs;
				if (rightTmp)
					rightTmp->parent = &rhs;

				Node * parentTmp = parent;

				parent = rhs.parent == this ? &rhs : rhs.parent;
				if (parent) {
					if (parent->left == &rhs)
						parent->left = this;
					else if (parent->right == &rhs)
						parent->right = this;
				}

				rhs.parent = parentTmp;
				if (rhs.parent) {
					if (rhs.parent->left == this)
						rhs.parent->left = &rhs;
					else if (parent->right == this)
						rhs.parent->right = &rhs;
				}

				std::swap(height, rhs.height);
				std::swap(data, rhs.data);
		}

		}; // Node

		template<typename ItT, int B> //ItT = Node * , T = pair<Key, mapped_type>
		class TreeIterator {
			// protected:
			protected:
				ItT _current;

			public:
				TreeIterator(): _current(0) {}
				TreeIterator(ItT current): _current(current) {}
				TreeIterator(const TreeIterator & rhs) { *this = rhs; }
				~TreeIterator() {}


				TreeIterator & operator=(const TreeIterator & rhs) {
					if (this != &rhs) {
						_current = rhs.getCurrent();
					}
					return *this;
				}

				T & operator*(void) { return _current->data; }
				const T & operator*(void) const { return _current->data; }

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
					else _current = _goMaxLeft(_current->right);

					return *this;
				}
				ItT getCurrent(void) const { return this->_current; }

				TreeIterator operator++(int) {
					TreeIterator it(*this);
					operator++();
					return it;
				}

				TreeIterator & operator--(void) {
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
				TreeConstIterator() { this->_current = 0; }
				TreeConstIterator(ItT current) { this->_current = current; }
				TreeConstIterator(const TreeIterator<ItT, 0> & rhs) { this->_current = rhs.getCurrent(); }
				TreeConstIterator(const TreeConstIterator & rhs): TreeIterator<ItT, B>(rhs) { *this = rhs; }
				~TreeConstIterator() {}

				TreeConstIterator & operator=(const TreeConstIterator & rhs) {
					if (this != &rhs) {
						this->_current = rhs.getCurrent();
					}
					return *this;
				}

				const T & operator*(void) const { return this->_current->data; }
				const T * operator->(void) const { return &this->_current->data; }
				const ItT getCurrent(void) const { return this->_current; }

		};

		template<typename ItT, int B>
		class TreeReverseIterator: public TreeIterator<ItT, B> {
			public:
				TreeReverseIterator() { this->_current = 0; }
				TreeReverseIterator(ItT current) { this->_current = current; }
				TreeReverseIterator(const TreeReverseIterator & rhs): TreeIterator<ItT, B>(rhs) { *this = rhs; }
				TreeReverseIterator(const TreeIterator<ItT, 0> & rhs) { this->_current = rhs.getCurrent(); }
				~TreeReverseIterator() {}

				TreeReverseIterator & operator=(const TreeReverseIterator & rhs) {
					if (this != &rhs) {
						this->_current = rhs.getCurrent();
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
					this->operator--();
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
					this->operator++();
					return it;
				}

				TreeIterator<ItT, 0> base() const { return TreeIterator<ItT, 0>(this->getCurrent()); }

				bool operator!=(TreeReverseIterator<ItT, 2> rhs) const { return this->base() != rhs.base(); }
				bool operator==(TreeReverseIterator<ItT, 2> rhs) const { return this->base() == rhs.base(); }

				bool operator==(TreeReverseIterator<ItT, 3> rhs) const { return this->base() == rhs.base(); }
				bool operator!=(TreeReverseIterator<ItT, 3> rhs) const { return this->base() != rhs.base(); }
		};

		template<typename ItT, int B>
		class TreeConstReverseIterator: public TreeIterator<ItT, B> {

			public:
				TreeConstReverseIterator() { this->_current = 0; }
				TreeConstReverseIterator(ItT current) { this->_current = current; }
				TreeConstReverseIterator(const TreeConstReverseIterator & rhs): TreeIterator<ItT, B>(rhs) { *this = rhs; }
				TreeConstReverseIterator(const TreeReverseIterator<ItT, 2> & rhs) { this->_current = rhs.getCurrent(); }
				TreeConstReverseIterator(const TreeConstIterator<ItT, 1> & rhs) { this->_current = rhs.getCurrent(); }
				TreeConstReverseIterator(const TreeIterator<ItT, 0> & rhs) { this->_current = rhs.getCurrent(); }
				~TreeConstReverseIterator() {}

				TreeConstReverseIterator & operator=(const TreeConstReverseIterator & rhs) {
					if (this != &rhs) {
						this->_current = rhs.getCurrent();
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
				const ItT getCurrent(void) const { return this->_current; }

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
					this->operator--();
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
					this->operator++();
					return it;
				}

				// TreeIterator<ItT, 1> base() const { return TreeConstIterator<ItT, 0>(this->getCurrent()); }

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
		BTree(const BTree & rhs):	_root(_copyRoot(_allocator, rhs._root)),
									_size(rhs._size),
									_comp(rhs._comp),
									_allocator(rhs._allocator),
									_begin(_root ? _goMaxLeft(_root) : allocateNode(T(), 0)),
									_end(_root ? _goMaxRight(_root) : allocateNode(T(), 0)) {}
		~BTree() {
			this->clear(this->_root);
			if (_begin) {
				this->_allocator.destroy(_begin);
				this->_allocator.deallocate(_begin, 1);
			}
			if (_end) {
				this->_allocator.destroy(_end);
				this->_allocator.deallocate(_end, 1);
			}
		}

		BTree & operator=(const BTree & rhs) {
			if (this != &rhs) {
				this->clear(this->_root);
				if (_begin) {
				this->_allocator.destroy(_begin);
				this->_allocator.deallocate(_begin, 1);
				}
				if (_end) {
					this->_allocator.destroy(_end);
					this->_allocator.deallocate(_end, 1);
				}
				this->_root = _copyRoot(this->_allocator, rhs._root);
				this->_size = rhs._size;
				this->_comp = rhs._comp;
				this->_allocator = rhs._allocator;
				this->_begin = _root ? _goMaxLeft(this->_root) : allocateNode(T(), 0);
				this->_end = _root ? _goMaxRight(this->_root) : allocateNode(T(), 0);
			}
			return *this;
		}

		Node * _getRoot() const { return this->_root; }

		static Node * allocateNode(const_reference value, Node * parent, Node * left = 0, Node * right = 0, int height = 0) {
			std::allocator<Node> alloc;
			Node * node = alloc.allocate(1);

			alloc.construct(node, Node(value, parent, left, right, height));
			return node;
		}

		Node * addNode(const T & value, Node * & root, Node * parent = 0) {
			if (!root) {
				++this->_size;
				if (!_begin)
					_begin = allocateNode(T(), 0);
				if (!_end)
					_end = allocateNode(T(), 0);
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
			else {
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
				return ft::pair<iterator, bool>(iterator(insertedNode), false);

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

			return ft::pair<iterator, bool>(iterator(insertedNode), true);
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

		Node * LLRotate(Node * p){
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
			
			return pl;
		}

		Node * LRRotate(Node * p) {
			Node * pl = p->left;
			Node * plr = pl->right;

			if (p == _root)
				_root = plr;
			if (p->parent) {
				if (p->parent->right == p)
					p->parent->right = plr;
				else p->parent->left = plr;
			}

			p->left = plr->right;
			if (plr->right)
				plr->right->parent = p;

			pl->right = plr->left;
			if (plr->left)
				plr->left->parent = pl;

			plr->parent = p->parent;
			plr->left = pl;
			plr->right = p;

			p->parent = plr;
			pl->parent = plr;

			return plr;
		}

		Node * RRRotate(Node * p) {
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

			return pr;
		}

		Node * RLRotate(Node * p) {
			Node * pr = p->right;
			Node * prl = pr->left;

			if (p == _root)
				_root = prl;
			if (p->parent) {
				if (p->parent->right == p)
					p->parent->right = prl;
				else p->parent->left = prl;
			}

			p->right = prl->left;
			if (prl->left)
				prl->left->parent = p;

			pr->left = prl->right;
			if (prl->right)
				prl->right->parent = pr;

			prl->parent = p->parent;
			prl->left = p;
			prl->right = pr;

			p->parent = prl;
			pr->parent = prl;

			return prl;
		}

		Node * rebalanceTree(Node * root) {
			Node * tmp = root;

			while (tmp) {
				tmp->height = getNodeHeight(tmp);
				#ifdef DEBUG
					std::cout << "rebalance: " << tmp->data.first << ' ' << tmp->data.second << ' ';
				#endif
				int bf = getBF(tmp), bf2 = 0;

				#ifdef DEBUG
					std::cout << "bf: " << bf << '\n';
				#endif
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

		void swap(BTree & rhs) {
			if (this != &rhs) {
				std::swap(this->_root, rhs._root);
				std::swap(this->_begin, rhs._begin);
				std::swap(this->_end, rhs._end);
				std::swap(this->_size, rhs._size);
				std::swap(this->_allocator, rhs._allocator);
			}
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
			return iterator(tmp ? tmp : _end);
		}

		const_iterator begin() const {
			Node * tmp = this->_root;

			while (tmp && tmp->left && tmp->left != _begin)
				tmp = tmp->left;
			return const_iterator(tmp ? tmp : _end);
		}

		iterator end() { return iterator(_end); }
		const_iterator end() const { return const_iterator(_end); }

		reverse_iterator rbegin() { return reverse_iterator(_end); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_end); }

		reverse_iterator rend() { return reverse_iterator(_root ? _getFirst(_root, _begin) : _end); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_root ? _getFirst(_root, _begin) : _end); }

		size_type getSize() const { return this->_size; }

		size_type getMaxSize() const { return this->_allocator.max_size(); }

		Node * _copyRoot(NodeAllocator & alloc, Node * p, Node * parent = 0) const {
			if (!p)
				return 0;

			Node * newNode = allocateNode(p->data, parent, 0, 0, p->height);

			newNode->left = _copyRoot(alloc, p->left, newNode);
			newNode->right = _copyRoot(alloc, p->right, newNode);

			return newNode;
		}

		void clear(Node * root) {
			if (!root)
				return ;
			if (root->right)
				clear(root->right);
			if (root->left)
				clear(root->left);

			if (root == _root) {
				this->_allocator.destroy(root);
				this->_allocator.deallocate(root, 1);
				_root = 0;
				_size = 0;
				_end = allocateNode(T(), 0);
				_begin = allocateNode(T(), 0);
			}
			else {
				this->_allocator.destroy(root);
				this->_allocator.deallocate(root, 1);
			}
		}

		Node * deleteNode(Node * root, const T & value) {
			if (!root)
				return 0;

			if (!_comp(value.first, root->data.first) && !_comp(root->data.first, value.first)) {
				if (root == _end || root == _begin)
					return root;

				if (root->left == _begin && root->right == _end) {
					this->_allocator.destroy(root);
					this->_allocator.deallocate(root, 1);
					_root = 0;
					--_size;
					return 0;
				}

				if ((!root->left && !root->right) || (!root->left && root->right == _end) || (!root->right && root->left == _begin)) {
					if (root->left == _begin) {
						_begin->parent = root->parent;
						root->parent->left = _begin;
					}
					else if (root->right == _end) {
						_end->parent = root->parent;
						root->parent->right = _end;
					}
					else {
						if (root->parent) {
							if (root->parent->left == root)
								root->parent->left = 0;
							else root->parent->right = 0;
						}
					}

					Node * ret = (!root->left && !root->right) ? 0 : (root->left ? _begin : _end);
					this->_allocator.destroy(root);
					this->_allocator.deallocate(root, 1);
					--_size;

					return ret;
				}

				bool leftSide;
				if ((root->left && root->left != _begin) && (root->right && root->right != _end))
					leftSide = root->left->height >= root->right->height;
				else leftSide = (root->left && root->left != _begin);

				Node* tmp = leftSide ? _goMaxRight(root->left) : _goMaxLeft(root->right);

				root->swap(*tmp);

				std::swap(root, tmp);
				root->data = tmp->data;

				if (leftSide)
					root->left = deleteNode(root->left, tmp->data);
				else root->right = deleteNode(root->right, tmp->data);
			}
			else {
				if (_comp(value.first, root->data.first))
					root->left = deleteNode(root->left, value);
				else root->right = deleteNode(root->right, value);
			}

			root->height = getNodeHeight(root);
			int bf = getBF(root), bf2 = 0;

			if (bf == 2) {
				bf2 = getBF(root->left);

				if (bf2 == 1)
					return LLRotate(root);
				else if (bf2 == -1)
					return LRRotate(root);
				else if (bf2 == 0)
					return LLRotate(root);
			}
			else if (bf == -2) {
				bf2 = getBF(root->right);

				if (bf2 == 1)
					return RLRotate(root);
				else if (bf2 == -1)
					return RRRotate(root);
				else if (bf2 == 0)
					return RRRotate(root);
			}

			return root;
		}

		void erase(iterator position) { _root = deleteNode(_root, position.getCurrent()->data); }

		size_type erase(Node * toDel) {
			size_type oldSize = this->_size;

			# ifdef DEBUG
				std::cout << "Deleting: (" << toDel->data.first << ':' << toDel->data.second << ")\n";
			# endif
			_root = deleteNode(_root, toDel->data);
			// print2D();
			return oldSize - this->_size;
		}

		void erase(iterator first, iterator last) {
			Node * tmp = 0;
			while (first != last) {
				tmp = first.getCurrent();
				++first;
				_root = deleteNode(_root, tmp->data);
			}
		}

		Node * findLowerBound(Node* root, const_reference value, Node* last = 0) const {
			if (!root || root == _begin || root == _end)
				return last;

			if (_comp(root->data.first, value.first))
				return findLowerBound(root->right, value, last);
			else
				return findLowerBound(root->left, value, root);
		}

		Node* findUpperBound(Node* root, const_reference value, Node* last = 0) const {
			if (!root || root == _begin || root == _end)
				return last;

			if (_comp(root->data.first, value.first) || (!_comp(root->data.first, value.first) && !_comp(value.first, root->data.first)))
				return findUpperBound(root->right, value, last);
			else
				return findUpperBound(root->left, value, root);
		}

		iterator lower_bound(const_reference value) {
			Node * p = findLowerBound(_root, value);

			return p ? iterator(p) : end();
		}

		const_iterator lower_bound(const_reference value) const {
			Node * p = findLowerBound(_root, value);

			return p ? const_iterator(p) : end();
		}

		iterator upper_bound(const_reference value) {
			Node * p = findUpperBound(_root, value);

			return p ? iterator(p) : end();
		}

		const_iterator upper_bound(const_reference value) const {
			Node * p = findUpperBound(_root, value);


			return p ? const_iterator(p) : end();
		}

		ft::pair<iterator, iterator> equal_range(const_reference value) { return ft::make_pair(lower_bound(value), upper_bound(value)); }

		ft::pair<const_iterator, const_iterator> equal_range(const_reference value) const { return ft::make_pair(lower_bound(value), upper_bound(value)); }

	}; // BTree

	template<typename T, typename Compare, typename Alloc>
	bool operator==(const BTree<T, Compare, Alloc> & lhs, const BTree<T, Compare, Alloc> & rhs) {
		if (lhs.getSize() != rhs.getSize())
			return false;

		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<typename T, typename Compare, typename Alloc>
	bool operator!=(const BTree<T, Compare, Alloc> & lhs, const BTree<T, Compare, Alloc> & rhs) { return !(lhs == rhs); }

	template<typename T, typename Compare, typename Alloc>
	bool operator<(const BTree<T, Compare, Alloc> & lhs, const BTree<T, Compare, Alloc> & rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template<typename T, typename Compare, typename Alloc>
	bool operator>(const BTree<T, Compare, Alloc> & lhs, const BTree<T, Compare, Alloc> & rhs) { return rhs < lhs; }

	template<typename T, typename Compare, typename Alloc>
	bool operator<=(const BTree<T, Compare, Alloc> & lhs, const BTree<T, Compare, Alloc> & rhs) { return !(lhs > rhs); }

	template<typename T, typename Compare, typename Alloc>
	bool operator>=(const BTree<T, Compare, Alloc> & lhs, const BTree<T, Compare, Alloc> & rhs) { return !(lhs < rhs); }

} // namespace ft

# endif // __RBTREE_HPP__