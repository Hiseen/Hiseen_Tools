#pragma once
#include <cassert>
namespace Hiseen_Tools
{
	template<typename T>
	class SegmentTreeNode
	{
	public:
		int left;
		int right;
		T data;
		SegmentTreeNode<T>* lchild;
		SegmentTreeNode<T>* rchild;
		static SegmentTreeNode<T>* Create(int l, int r)
		{
			assert(r - l >= 1);
			SegmentTreeNode<T>* root = new SegmentTreeNode<T>(l, r);
			if (r - l == 1)
				return root;
			else if (r - l > 1)
			{
				int mid = l + ((r - l) >> 1);
				root->lchild = Create(l, mid);
				root->rchild = Create(mid, r);
			}
			return root;
		}
		void Insert(int l, int r,const function<bool(SegmentTreeNode<T>* node,int l,int r)>& f)
		{
			assert(l >= left && r <= right);

			if (f(this, l, r))return;
			int mid = left + ((right - left) >> 1);
			if (r <= mid)
			{
				assert(lchild);
				lchild->Insert(l, r,f);
			}
			else if (l >= mid)
			{
				assert(rchild);
				rchild->Insert(l, r,f);
			}
			else
			{
				assert(lchild && rchild);
				lchild->Insert(l, mid,f);
				rchild->Insert(mid, r,f);
			}
		}
		void Delete(int l, int r, const function<bool(SegmentTreeNode<T>* node, int l, int r)>& f)
		{
			assert(l >= left && r <= right);
			if (f(this, l, r))return;
			int mid = left + ((right - left) >> 1);
			if (r <= mid)
			{
				assert(lchild);
				lchild->Delete(l, r,f);
			}
			else if (l >= mid)
			{
				assert(rchild);
				rchild->Delete(l, r,f);
			}
			else
			{
				assert(lchild && rchild);
				lchild->Delete(l, mid,f);
				rchild->Delete(mid, r,f);
			}
		}
	private:
		SegmentTreeNode<T>(int l = 0, int r = 0, SegmentTreeNode<T>* lc = nullptr, SegmentTreeNode<T>* rc = nullptr):data()
		{
			left = l;
			right = r;
			lchild = lc;
			rchild = rc;
		}
	};

	
}
