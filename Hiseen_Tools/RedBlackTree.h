#pragma once
#include <functional>
#include <map>
using namespace std;
namespace Hiseen_Tools
{
	template<typename T, typename Compare=less<T>>
	class RedBlackTree
	{
		static const bool RED = true;
		static const bool BLACK = false;
	public:
		RedBlackTree() 
		{
			root = nullptr;
		};
		void Insert(const T& t)
		{
			if (!root)
				root = new RedBlackTreeNode<T, Compare>(t, BLACK);
			else
				root=RedBlackTreeNode<T, Compare>::Insert(root, t,comp);
		}
		void Delete(const T& t)
		{
			root=RedBlackTreeNode<T, Compare>::Delete(root, t,comp);
			root->color = BLACK;
		}
		T* Search(const T& t)
		{
			RedBlackTreeNode<T, Compare>* result = RedBlackTreeNode<T, Compare>::Search(root, t,comp);
			return result ? nullptr : &result->value;
		}
		~RedBlackTree() 
		{
			if (root)
				delete root;
		};
	private:
		template<typename T,typename Compare=less<T>>
		class RedBlackTreeNode
		{
		public:
			typedef RedBlackTreeNode<T, Compare> Node;
			T value;
			Node* left;
			Node* right;
			bool color;
			Node(const T& t,bool c)
			{
				color = c;
				value = t;
				left = nullptr;
				right = nullptr;
			}
			~RedBlackTreeNode<T, Compare>()
			{
				if (left)
					delete left;
				if (right)
					delete right;
			}
			static Node* Insert(Node* n, const T& t,const Compare& comp)
			{
				if (!n)return new Node(t, RED);
				if (IsRed(n->left) && IsRed(n->right))
					ColorFlip(n);
				if (comp(n->value, t))n->right = Insert(n->right, t,comp);
				else n->left = Insert(n->left, t,comp);
				if (IsRed(n->right))
					n = RotateLeft(n);
				if (IsRed(n->left) && IsRed(n->left->left))
					n = RotateRight(n);
				return n;
			}

			static Node* Search(Node* n, const T& t,const Compare& comp)
			{
				if (comp(n->value, t))return n->right ? Search(n->right, t,comp) : nullptr;
				else if (comp(t, n->value))return n->left ? Search(n->left, t,comp) : nullptr;
				else return n;
			}

			static Node* Delete(Node* n, const T& t, const Compare& comp)
			{
				if (!n)return nullptr;
				int cmp = comp(n->value, t) ? 1 : (comp(t, n->value) ? -1 : 0);
				if (cmp < 0)
				{
					if (n->left && !IsRed(n->left) && !IsRed(n->left->left))
						n = MoveRedLeft(n);
					n->left = Delete(n->left, t,comp);
				}
				else
				{
					if (IsRed(n->left))n = MoveRedRight(n);
					if (!cmp && !n->right)
					{
						delete n;
						return nullptr;
					}
					if (n->right && !IsRed(n->right) && !IsRed(n->right->left))
						n = MoveRedRight(n);
					if (!cmp)
					{
						n->value = FindMin(n->right);
						n->right = DeleteMin(n->right);
					}
					else
						n->right = Delete(n->right, t,comp);
				}
				return FixUp(n);
			}
		private:
			static bool IsRed(Node* n)
			{
				if (!n)return false;
				return n->color;
			}

			static Node* RotateLeft(Node* n)
			{
				Node* x = n->right;
				n->right = x->left;
				x->left = n;
				x->color = x->left->color;
				x->left->color = RED;
				return x;
			}

			static Node* RotateRight(Node* n)
			{
				Node* x = n->left;
				n->left = x->right;
				x->right = n;
				x->color = x->right->color;
				x->right->color = RED;
				return x;
			}

			static void ColorFlip(Node* n)
			{
				n->color = !n->color;
				if(n->left)n->left->color = !n->left->color;
				if(n->right)n->right->color = !n->right->color;
			}
			
			static Node* MoveRedRight(Node* n)
			{
				ColorFlip(n);
				if (IsRed(n->left->left))
				{
					n = RotateRight(n);
					ColorFlip(n);
				}
				return n;
			}

			static Node* MoveRedLeft(Node* n)
			{
				ColorFlip(n);
				if (IsRed(n->right->left))
				{
					n->right = RotateRight(n->right);
					n = RotateLeft(n);
					ColorFlip(n);
				}
				return n;
			}

			static Node* FixUp(Node* n)
			{
				if (IsRed(n->right))
					n = RotateLeft(n);
				if (IsRed(n->left) && IsRed(n->left->left))
					n = RotateRight(n);
				if (IsRed(n->left) && IsRed(n->right))
					ColorFlip(n);
				return n;
			}

			static Node* DeleteMin(Node* n)
			{
				if (!n->left)
				{
					delete n;
					return nullptr;
				}
				if (IsRed(n->left) && IsRed(n->left->left))
					n = MoveRedLeft(n);
				n->left = DeleteMin(n->left);
				return FixUp(n);
			}

			static const T& FindMin(Node* n)
			{
				while (n->left)
					n = n->left;
				return n->value;
			}

			static const T& FindMax(Node* n)
			{
				while (n->right)
					n = n->right;
				return n->value;
			}
		};
		RedBlackTreeNode<T, Compare>* root;
		Compare comp;
	};
}

