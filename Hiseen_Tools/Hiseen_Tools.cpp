// Hiseen_Tools.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "UnionFind.h"
#include "Trie.h"
#include "BinaryIndexedTree.h"
using namespace Hiseen_Tools;

int main()
{
	Trie<26,char> t([](const char c) {return (int)(c - 'a'); });
	t.Insert("apple");
	t.Insert("banana");
	t.Insert("opposite");
	string a = "tutututu";
	t.Insert(a);
	bool result=t.Search("peach");
	result = t.Search("banana");
	result = t.Search(a);
	t.Remove("ooooooo");
	t.Remove("apple");
	t.Remove(a);
	result = t.Search("apple");

	BinaryIndexedTree<32, int> bit;
	bit.Modify(1, 1);
	bit.Modify(2, 1);
	cout<<bit.GetSum(2);
    return 0;
}

