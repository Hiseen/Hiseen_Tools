#pragma once
#include <cassert>
namespace Hiseen_Tools
{
	template<int Size, typename T>
	class BinaryIndexedTree
	{
	public:
		BinaryIndexedTree()
		{
			for (int i = 1; i <= Size; ++i)
				data[i] = T();
		}

		BinaryIndexedTree(const T t[])
		{
			for (int i = 1; i <= Size; ++i)
			{
				data[i] = t[i];
				for (int j = i - 1; j>i - lowbit(i); --j)
					data[i] += t[j];
			};
		};
		BinaryIndexedTree(const vector<T>& t)
		{
			assert(t.size()==Size)
			for (int i = 1; i <= Size; ++i)
			{
				data[i] = t[i];
				for (int j = i - 1; j>i - lowbit(i); --j)
					data[i] += t[j];
			};
		}
		T GetSum(int index)
		{
			int s = 0;
			while (index > 0) {
				s += data[index];
				index -= lowbit(index);
			}
			return s;
		}
		void Modify(int index, T d)
		{
			assert(index != 0);
			while (index <= Size) {
				data[index] += d;
				index += lowbit(index);
			}
		}
		~BinaryIndexedTree() {};
	private:
		int lowbit(int x) { return x&(-x); };
		T data[Size+1];
	};
}

