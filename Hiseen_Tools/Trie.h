#pragma once
#include <memory>
#include <cassert>
#include <functional>
using namespace std;

namespace Hiseen_Tools
{
	template<int Size>
	class TrieNode
	{
	public:
		int count;
		TrieNode<Size>* children[Size];
		bool IsEnd;
		TrieNode(int index = -1) : count(0)
		{
			assert(index < Size);
			for (int i = 0; i < Size; ++i)
				children[i] = nullptr;
			if (index != -1)children[index] = new TrieNode();
			IsEnd = false;
		}
		inline TrieNode<Size>* GetSubNode(int index)
		{
			assert(index < Size);
			return children[index];
		}
		TrieNode<Size>* insert(int index, bool end = false)
		{
			TrieNode<Size> *node = GetSubNode(index);
			if (!node)
				node = new TrieNode();
			node->count++;
			node->IsEnd = end;
			children[index] = node;
			return node;
		}
		TrieNode<Size>* remove(int index, bool isend = false)
		{
			TrieNode<Size>* node = GetSubNode(index);
			if (node->count == 1)
			{
				delete node;
				node = nullptr;
				children[index] = nullptr;
			}
			else
			{
				node->count--;
				if (isend)node->IsEnd = false;
			}
			return node;
		}



		~TrieNode()
		{
			for (int i = 0; i < Size; ++i)
			{
				if (children[i])
				{
					delete children[i];
					children[i] = nullptr;
				}
			}
		}
	};

	template<int Size, typename T>
	class Trie
	{
	public:
		Trie(const function<int(const T&)>& f, const function<T(int)>& r)
		{
			root = new TrieNode<Size>();
			conversion = f;
			reversion = r;
		};

		void Insert(const T t[])
		{
			if (Search(t))return;
			auto node = root;
			int len = (sizeof(t) / sizeof(T));
			for (int i = 0; i < len; ++i)
				node = node->insert(conversion(t[i]), i == len - 1);
		}
		void Insert(const vector<T>& t)
		{
			if (Search(t))return;
			auto node = root;
			int len = t.size();
			for (int i = 0; i < len; ++i)
				node = node->insert(conversion(t[i]), i == len - 1);
		}

		void Remove(const T t[])
		{
			if (!Search(t))return;
			auto node = root;
			int len = (sizeof(t) / sizeof(T));
			int now = 0;
			while (node && now != len)
			{
				node = node->remove(conversion(t[now]), now == len - 1);
				now++;
			}
		}

		void Remove(const vector<T>& t)
		{
			if (!Search(t))return;
			auto node = root;
			int len = t.size();
			int now = 0;
			while (node && now != len)
			{
				node = node->remove(conversion(t[now]), now == len - 1);
				now++;
			}
		}
		
		bool Search(const T t[])
		{
			auto node = root;
			int len = (sizeof(t) / sizeof(T));
			for (int i = 0; i < len; ++i)
			{
				node = node->GetSubNode(conversion(t[i]));
				if (!node)return false;
			}
			return node->IsEnd;
		}

		bool Search(const vector<T>& t)
		{
			auto node = root;
			int len = t.size();
			for (int i = 0; i < len; ++i)
			{
				node = node->GetSubNode(conversion(t[i]));
				if (!node)return false;
			}
			return node->IsEnd;
		}

		vector<vector<T>> GetSuffix(const T t[])
		{
			vector<vector<T>> res;
			auto node = root;
			int len = (sizeof(t) / sizeof(T));
			for (int i = 0; i < len; ++i)
			{
				node = node->GetSubNode(conversion(t[i]));
				if (!node)return res;
			}
			RecAdd(node, {}, res);
			return res;
		}

		vector<vector<T>> GetSuffix(const vector<T>& t)
		{
			vector<vector<T>> res;
			auto node = root;
			int len = t.size();
			for (int i = 0; i < len; ++i)
			{
				node = node->GetSubNode(conversion(t[i]));
				if (!node)return res;
			}
			RecAdd(node, vector<T>{}, res);
			return res;
		}
		~Trie()
		{
			if (root)
				delete root;
		};
	private:
		TrieNode<Size>* root;
		function<int(const T&)> conversion;
		function<T(int)> reversion;
		void RecAdd(TrieNode<Size>* t, vector<T>& temp, vector<vector<T>>& res)
		{
			if (t->IsEnd)
				res.push_back(temp);
			for (int i = 0; i < Size; i++)
			{
				TrieNode<Size>* node = t->GetSubNode(i);
				if (node)
				{
					vector<T> temp1(temp);
					temp1.push_back(reversion(i));
					RecAdd(node, temp1, res);
				}
			}
		}
	};

	//ÌØ»¯char
	template<int Size>
	class Trie<Size, char>
	{
	public:
		Trie(const function<int(const char)>& f,const function<char(int)>& r)
		{
			root = new TrieNode<Size>();
			conversion = f;
			reversion = r;
		};

		void Insert(const char* t)
		{
			if (Search(t))return;
			auto node = root;
			int len = strlen(t);
			for (int i = 0; i < len; ++i)
				node = node->insert(conversion(t[i]), i == len - 1);
		}
		void Insert(const string& s)
		{
			if (Search(s))return;
			auto node = root;
			int len = s.size();
			for (int i = 0; i < len; ++i)
				node = node->insert(conversion(s[i]), i == len - 1);
		}

		void Remove(const char* t)
		{
			if (!Search(t))return;
			auto node = root;
			int len = strlen(t);
			int now = 0;
			while (node && now != len)
			{
				node = node->remove(conversion(t[now]), now == len - 1);
				now++;
			}
		}

		void Remove(const string& s)
		{
			if (!Search(s))return;
			auto node = root;
			int len = s.size();
			int now = 0;
			while (node && now != len)
			{
				node = node->remove(conversion(s[now]), now == len - 1);
				now++;
			}
		}
		bool Search(const char* t)
		{
			auto node = root;
			int len = strlen(t);
			for (int i = 0; i < len; ++i)
			{
				node = node->GetSubNode(conversion(t[i]));
				if (!node)return false;
			}
			return node->IsEnd;
		}

		bool Search(const string& s)
		{
			auto node = root;
			int len = s.size();
			for (int i = 0; i < len; ++i)
			{
				node = node->GetSubNode(conversion(s[i]));
				if (!node)return false;
			}
			return node->IsEnd;
		}
		vector<string> GetSuffix(const char* t)
		{
			vector<string> res;
			auto node = root;
			int len = strlen(t);
			for (int i = 0; i < len; ++i)
			{
				node = node->GetSubNode(conversion(t[i]));
				if (!node)return res;
			}
			RecAdd(node,string(""),res);
			return res;
		}
		vector<string> GetSuffix(const string& s)
		{
			vector<string> res;
			auto node = root;
			int len = s.size();
			for (int i = 0; i < len; ++i)
			{
				node = node->GetSubNode(conversion(s[i]));
				if (!node)return res;
			}
			RecAdd(node, "", res);
			return res;
		}
		~Trie()
		{
			if (root)
				delete root;
		};
	private:
		TrieNode<Size>* root;
		function<int(const char)> conversion;
		function<char(int)> reversion;
		void RecAdd(TrieNode<Size>* t, string& temp, vector<string>& res)
		{
			if (t->IsEnd)
				res.push_back(temp);
			for (int i = 0; i < Size; i++)
			{
				TrieNode<Size>* node = t->GetSubNode(i);
				if (node)
				{
					string temp1(temp);
					temp1+=reversion(i);
					RecAdd(node, temp1, res);
				}
			}
		}
	};
}