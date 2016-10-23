#pragma once
#include <vector>
using namespace std;

namespace Hiseen_Tools
{
	class UnionFind
	{
	public:
		UnionFind(int size):id(size),sz(size,1)
		{
			count = size;
			for (int i = 0; i < size; ++i)
				id[i] = i;
		}
		inline int Count() { return count; }
		inline int SizeOfSet(int p) { return sz[Find(p)]; }
		int Find(int p)
		{
			while (p != id[p])
			{
				id[p] = id[id[p]];
				p = id[p];
			}
			return p;
		}
		inline bool IsConnected(int p, int q)
		{
			return Find(p) == Find(q);
		}
		void Union(int p, int q)
		{
			int rootp = Find(p);
			int rootq = Find(q);
			if (rootp == rootq)return;
			if (sz[rootp] > sz[rootq])
			{
				id[rootq] = rootp;
				sz[rootp] += sz[rootq];
			}
			else
			{
				id[rootp] = rootq;
				sz[rootq] += sz[rootp];
			}
			count--;
		}
		~UnionFind() {};
	private:
		vector<int> id;// tree struct
		vector<int> sz;// store sizes
		int count;
	};
}

