#pragma once
#include <functional>
#include <cassert>
using namespace std;
namespace Hiseen_Tools
{
	constexpr int Prime[10] = { 2,3,5,7,11,13,17,19,23,29 };

	template<typename T1,typename T2>
	class HashTree
	{
	public:
		HashTree<T1,T2>(const function<int(const T1&)>& f):conversion(f)
		{
			size = 0;
			root = new HashTreeNode<0, T1,T2>();
		};

		bool Insert(const T1& t1,const T2& t2)
		{
			auto ans = Search(t1);
			if (ans && *ans == t2)return false;
			bool result=root->Insert(conversion(t1), t1, t2);
			if (result)size++;
			return result;
		}

		T2* Search(const T1& t1)
		{
			return root->Search(conversion(t1), t1);
		}

		bool Delete(const T1& t1)
		{
			auto ans = Search(t1);
			if (!ans)return false;
			bool result=root->Delete(conversion(t1), t1);
			if (result)size--;
			return result;
		}

		inline int GetSize()const
		{
			return size;
		}

		~HashTree<T1,T2>() 
		{
			delete root;
		};
	private:
		template<int Sizeindex, typename T1,typename T2>
		class HashTreeNode
		{
		public:
			typedef HashTreeNode<Sizeindex + 1, T1, T2> ChildType;
			bool occupied;
			T1 key;
			T2* value;
			ChildType* children[Prime[Sizeindex]];
			HashTreeNode<Sizeindex, T1,T2>() : key(),value()
			{
				occupied = false;
				int size = Prime[Sizeindex];
				for (int i = 0; i < size; i++)
					children[i] = nullptr;
			}
			bool Insert(int key,const T1& t1, const T2& t2)
			{
				int index = key%Prime[Sizeindex];
				ChildType* temp = children[index];
				if (!temp)
				{
					temp = new ChildType();
					temp->occupied = true;
					temp->key = t1;
					temp->value = new T2(t2);
					children[index] = temp;
					return true;
				}
				else if (!temp->occupied)
				{
					temp->occupied = true;
					if (temp->value)
						delete temp->value;
					temp->value = new T2(t2);
					return true;
				}
				return temp->Insert(key, t1, t2);

			}
			T2* Search(int key, const T1& t1)
			{
				int index = key%Prime[Sizeindex];
				auto temp = children[index];
				if (!temp)return nullptr;
				if (temp && temp->occupied && temp->key == t1)
					return temp->value;
				return temp->Search(key, t1);
			}

			bool Delete(int key, const T1& t1)
			{
				int index = key%Prime[Sizeindex];
				auto temp = children[index];
				if (!temp)return false;
				if (temp && temp->occupied && temp->key == t1)
				{
					temp->occupied = false;
					return true;
				}
				return temp->Delete(key, t1);
			}
			~HashTreeNode<Sizeindex, T1,T2>()
			{
				int size = Prime[Sizeindex];
				if (value)
					delete value;
				for (int i = 0; i < size; i++)
					if (children[i])
					{
						delete children[i];
						children[i] = nullptr;
					}
			}

		};
		template<typename T1,typename T2>
		class HashTreeNode<9, T1,T2>
		{
		public:
			bool occupied;
			T1 key;
			T2* value;
			HashTreeNode<9, T1,T2>() :key()
			{
				occupied = false;
				value = nullptr;
			}
			bool Insert(int key, const T1& t1, const T2& t2)
			{
				return false;
			}
			T2* Search(int key, const T1& t1)
			{
				return nullptr;
			}
			bool Delete(int key, const T1& t1)
			{
				return false;
			}
			~HashTreeNode<9, T1, T2>()
			{
				if (value)
					delete value;
			}
		};
		HashTreeNode<0, T1,T2>* root;
		function<int(const T1&)> conversion;
		unsigned long size;
	};
}

