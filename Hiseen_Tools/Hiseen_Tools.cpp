// Hiseen_Tools.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "UnionFind.h"
#include "Trie.h"
#include "BinaryIndexedTree.h"
#include "SegmentTree.h"
using namespace Hiseen_Tools;

int main()
{
	Trie<26, char> t([](const char c) {return (int)(c - 'a'); }, [](int i) {return (char)(i + 'a'); });
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

    return 0;
}

