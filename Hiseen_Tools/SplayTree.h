#pragma once
#include <functional>
using namespace std;

namespace Hiseen_Tools
{
	template<typename T,typename Compare=less<T>>
	class SplayTree
	{
	public:
		template<typename T>
		class SplayTreeNode
		{
		public:
			SplayTreeNode<T>* left;
			SplayTreeNode<T>* right;
			SplayTreeNode<T>* parent;
			T value;
			SplayTreeNode<T>(SplayTreeNode<T>* pre = nullptr, const T& t = T(), SplayTreeNode<T>* l = nullptr, SplayTreeNode<T>* r = nullptr)
			{
				parent = pre;
				value = t;
				left = l;
				right = r;
			}
			~SplayTreeNode<T>()
			{
				if (left)
					delete left;
				if (right)
					delete right;
			}
		};
		SplayTree() 
		{
			root = nullptr;
			size = 0;
		};

		bool Insert(const T& t)
		{
			if (Search(t))return false;
			SplayTreeNode<T>* now = root;
			SplayTreeNode<T>* pre = nullptr;
			while (now)
			{
				pre = now;
				if (comp(now->value, t))now = now->right;
				else now = now->left;
			}
			now = new SplayTreeNode<T>(pre, t);
			if (!pre)root = now;
			else if (comp(pre->value, now->value))pre->right = now;
			else pre->left = now;
			Splay(now);
			size++;
			return true;
		}

		SplayTreeNode<T>* Search(const T& t)
		{
			SplayTreeNode<T>* result = root;
			while (result)
			{
				if (comp(result->value, t))result = result->right;
				else if (comp(t, result->value))result = result->left;
				else return result;
			}
			return nullptr;
		}

		bool Delete(const T& t)
		{
			SplayTreeNode<T>* now = Search(t);
			if (!now)return false;
			Splay(now);
			if (!now->left)
				Replace(now, now->left);
			else if (!now->right)
				Replace(now, now->right);
			else
			{
				SplayTreeNode<T>* min = GetMinNode(now->right);
				if (min->parent != now)
				{
					Replace(min, min->right);
					min->right = now->right;
					min->right->parent = min;
				}
				Replace(now, min);
				min->left = now->left;
				min->left->parent = min;
			}
			size--;
			return true;
		}

		bool IsEmpty()const
		{
			return !size;
		}

		~SplayTree() 
		{
			if (root)
				delete root;
		};
	private:
		void Zig(SplayTreeNode<T>* x)//right rotate
		{
			SplayTreeNode<T>* y = x->parent;
			y->left = x->right;
			if(x->right)x->right->parent = y;
			x->parent = y->parent;
			if (!y->parent)
				root = x;
			else if (y->parent->left == y)
				y->parent->left = x;
			else
				y->parent->right = x;
			x->right = y;
			y->parent = x;
		}

		void Zag(SplayTreeNode<T>* x)//left rotate
		{
			SplayTreeNode<T>* y = x->parent;
			y->right = x->left;
			if (x->left)x->left->parent = y;
			x->parent = y->parent;
			if (!y->parent)
				root = x;
			else if (y->parent->left == y)
				y->parent->left = x;
			else
				y->parent->right = x;
			x->left = y;
			y->parent = x;
		}

		void Splay(SplayTreeNode<T>* x)
		{
			while (x->parent)
			{
				if (!x->parent->parent)
				{
					if (x->parent->left == x)
						Zig(x);
					else
						Zag(x);
				}
				else if (x->parent->left == x && x->parent->parent->left == x->parent)
					Zig(x->parent), Zig(x);
				else if (x->parent->right == x && x->parent->parent->right == x->parent)
					Zag(x->parent), Zag(x);
				else if (x->parent->left == x && x->parent->parent->right == x->parent)
					Zig(x), Zag(x);
				else
					Zag(x), Zig(x);
			}
		}
		void Replace(SplayTreeNode<T>* dest, SplayTreeNode<T>* src)
		{
			if (!dest->parent)root = src;
			else if (dest->parent->left == src)dest->parent->left = src;
			else dest->parent->right = src;
			if (src)src->parent = dest->parent;
		}
		SplayTreeNode<T>* GetMaxNode(SplayTreeNode<T>* node)
		{
			while (node->right)node = node->right;
			return node;
		}
		SplayTreeNode<T>* GetMinNode(SplayTreeNode<T>* node)
		{
			while (node->left)node = node->left;
			return node;
		}
		SplayTreeNode<T>* root;
		Compare comp;
		unsigned long size;

	};
}
