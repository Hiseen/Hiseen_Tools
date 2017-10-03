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
	vector<string> re=t.GetWordsWithPrefix("app");
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
	*/
	RedBlackTree<int> rbt;
	for (int i = 0; i < 2000; i++)
		rbt.Insert(i);
	rbt.Search(250);
	rbt.Search(125);
	for (int i = 240; i >= 0; i--)
		rbt.Delete(i);
    return 0;
}

