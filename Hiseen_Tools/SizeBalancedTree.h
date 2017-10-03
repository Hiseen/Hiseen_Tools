#pragma once
#include <cassert>
#include <functional>
using namespace std;

namespace Hiseen_Tools
{
	template<typename T, typename Compare = less<T>>
	class SizeBalancedTree
	{
	public:
		template<typename T, typename Compare = less<T>>
		struct SBTNode
		{
			T value;
			int size;
			int count;
			SBTNode* left;
			SBTNode* right;
			SBTNode(const T& t)
			{
				size = 1;
				value = t;
				count = 0;
				left = nullptr;
				right = nullptr;
			}
			~SBTNode()
			{
				if (left)delete left;
				if (right)delete right;
			}
		};
		SBTNode<T, Compare>* root;

		SizeBalancedTree()
		{
			root = nullptr;
		}


		void Insert(const T& value)
		{
			auto temp = Search(value);
			if (temp) { temp->count++; return; }
			SBTInsert(root, value, comp);
		}

		bool Delete(const T& value)
		{
			
		}

		SBTNode<T, Compare>* Search(const T& value)
		{
			if (root == nullptr)return nullptr;
			else SBTSearch(root, value, comp);
		}

	private:
		typedef SBTNode<T, Compare> Node;
		static void Maintain(Node* t)
		{
			if (t==nullptr || t->left == nullptr || t->right == nullptr)return;
			if (t->left->left->size > t->right->size)
			{
				RightRotate(t);
				Maintain(t->right);
				Maintain(t);
			}
			else if (t->left->right->size > t->right->size)
			{
				LeftRotate(t->left);
				RightRotate(t);
				Maintain(t->left);
				Maintain(t->right);
				Maintain(t);
			}
			else if (t->right->right->size > t->left->size)
			{
				LeftRotate(t);
				Maintain(t->left);
				Maintain(t);
			}
			else if (t->right->left->size > t->right->size)
			{
				RightRotate(t->right);
				LeftRotate(t);
				Maintain(t->right);
				Maintain(t->left);
				Maintain(t);
			}

		}

		static void LeftRotate(Node*& t)
		{
			auto k = t->right;
			t->right = k->left;
			k->left = t;
			k->size = t->size;
			t->size = t->left->size + t->right->size + 1;
			t = k;
		}

		static void RightRotate(Node*& t)
		{
			auto k = t->left;
			t->left = k->right;
			k->right = t;
			k->size = t->size;
			t->size = t->left->size + t->right->size + 1;
			t = k;
		}
		static void SBTInsert(Node* t, const T& value, const Compare& comp)
		{
			if (t == nullptr)
				t = new SBTNode<T, Compare>(value);
			else
			{
				t->size += 1;
				if (comp(value, t->value))
					SBTInsert(t->left, value, comp);
				else
					SBTInsert(t->right, value, comp);
				Maintain(t);
			}
		}

		static Node* SBTSearch(Node* t, const T& value, const Compare& comp)
		{
			if (t->value == value)
				return t;
			else
			{
				if (comp(value, t->value))
				{
					if (t->left)SBTSearch(t->left, value, comp);
					else return nullptr;
				}
				else
				{
					if (t->right)SBTSearch(t->right, value, comp);
					else return nullptr;
				}
			}
		}

		Compare comp;
	};
}
