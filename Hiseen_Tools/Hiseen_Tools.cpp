// Hiseen_Tools.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "UnionFind.h"
#include "Trie.h"

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
    return 0;
}

