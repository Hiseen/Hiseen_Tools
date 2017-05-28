// Hiseen_Tools.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "UnionFind.h"
#include "Trie.h"
#include "BinaryIndexedTree.h"
#include "SegmentTree.h"
#include "HashTree.h"
#include "SplayTree.h"
#include "RedBlackTree.h"
using namespace Hiseen_Tools;

class WordDictionary {
public:
	template<int Size>
	class TrieNode
	{
	public:
		int count;
		TrieNode<Size>* children[Size];
		bool IsEnd;
		TrieNode(int index = -1) : count(0)
		{
			for (int i = 0; i < Size; ++i)
				children[i] = nullptr;
			if (index != -1)children[index] = new TrieNode();
			IsEnd = false;
		}
		bool Search(const string& word, int index)
		{
			if (index >= word.length())return false;
			char temp = word[index];
			if (temp == '.')
			{
				for (int i = 0; i<26; i++)
					if (children[i])
					{
						if (index == word.length() - 1 && children[i]->IsEnd)
							return true;
						else if (children[i]->Search(word, index + 1))
							return true;
					}
			}
			else
			{
				if (children[temp - 'a'])
				{
					if (index == word.length() - 1)
						return children[temp - 'a']->IsEnd;
					else return children[temp - 'a']->Search(word, index + 1);
				}
			}
			return false;

		}
		inline TrieNode<Size>* GetSubNode(int index)
		{
			assert(index < Size);
			return children[index];
		}
		TrieNode<Size>* insert(int index)
		{
			TrieNode<Size> *node = GetSubNode(index);
			if (!node)
				node = new TrieNode();
			node->count++;
			children[index] = node;
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
	template<int Size>
	class Trie
	{
	public:
		Trie()
		{
			root = new TrieNode<Size>();
		};
		void Insert(const string& s)
		{
			auto node = root;
			int len = s.size();
			for (int i = 0; i < len; ++i)
				node = node->insert(s[i] - 'a');
			node->IsEnd = true;
		}

		~Trie()
		{
			if (root)
				delete root;
		};
		TrieNode<Size>* root;
	};
	Trie<26> t;

	// Adds a word into the data structure.
	void addWord(string word) {
		t.Insert(word);
	}

	// Returns if the word is in the data structure. A word could
	// contain the dot character '.' to represent any one letter.
	bool search(string word) {
		bool temp=t.root->Search(word,0);
		cout << temp << endl;
		return temp;

	}
};
int main()
{
	/*Trie<26, char> t([](const char c) {return (int)(c - 'a'); }, [](int i) {return (char)(i + 'a'); });
	t.Insert("apple");
	t.Insert("banana");
	t.Insert("opposite");
	string a = "tutututu";
	t.Insert(a);
	bool result=t.Search("peach");
	result = t.Search("banana");
	result = t.Search(a);
	t.Remove("ooooooo");
	t.Insert("appooo");
	t.Insert("apppqwe");
	t.Remove(a);
	result = t.Search("apple");
	vector<string> re=t.GetSuffix("app");
	BinaryIndexedTree<32, int> bit;
	bit.Modify(1, 1);
	bit.Modify(2, 1);
	cout<<bit.GetSum(2);

	SegmentTreeNode<int>* root = SegmentTreeNode<int>::Create(1, 100);
	root->Insert(5, 20, [](SegmentTreeNode<int>* node, int l, int r) {if (node->left == l && node->right == r) { node->data++; return true; }return false;});

	HashTree<int, int> ht([](int a) {return a; });
	ht.Insert(12, 14);
	ht.Search(12);
	ht.Delete(12);
	ht.Search(12);
	ht.Insert(12, 19);
	ht.Insert(24, 355);

	SplayTree<int> st;
	st.Insert(100);
	st.Insert(250);
	st.Insert(350);
	st.Search(100);
	st.Search(200);
	st.Delete(250);
	st.Delete(500);

	RedBlackTree<int> rbt;
	for (int i = 0; i < 2000; i++)
		rbt.Insert(i);
	rbt.Search(250);
	rbt.Search(125);
	for (int i = 240; i >= 0; i--)
		rbt.Delete(i);
	*/
	WordDictionary wd;
	wd.addWord("at");
	wd.addWord("and");
	wd.addWord("an");
	wd.addWord("add");
	wd.search("a");
	wd.search(".at");
	wd.addWord("bat");
	wd.search(".at");
	wd.search("an.");
	wd.search("a.d.");
	wd.search("b.");
	wd.search("a.d");
	wd.search(".");
    return 0;
}

