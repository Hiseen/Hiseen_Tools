#pragma once
#include <cassert>
namespace Hiseen_Tools
{
	class SegmentTreeNode
	{
	public:
		int left;
		int right;
		int cover;
		SegmentTreeNode* lchild;
		SegmentTreeNode* rchild;
		static SegmentTreeNode* Create(int l, int r)
		{
			assert(r - l >= 1);
			SegmentTreeNode* root = new SegmentTreeNode(l, r);
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
		void Insert(int l, int r)
		{
			assert(l >= left && r <= right);
			if (left == l && right == r)
			{
				cover++;
				return;
			}
			int mid = left + ((right - left) >> 1);
			if (r <= mid)
			{
				assert(lchild);
				lchild->Insert(l, r);
			}
			else if (l >= mid)
			{
				assert(rchild);
				rchild->Insert(l, r);
			}
			else
			{
				assert(lchild && rchild);
				lchild->Insert(l, mid);
				rchild->Insert(mid, r);
			}
		}
		void Delete(int l, int r)
		{
			assert(l >= left && r <= right);
			if (left == l && right == r)
			{
				cover--;
				return;
			}
			int mid = left + ((right - left) >> 1);
			if (r <= mid)
			{
				assert(lchild);
				lchild->Delete(l, r);
			}
			else if (l >= mid)
			{
				assert(rchild);
				rchild->Delete(l, r);
			}
			else
			{
				assert(lchild && rchild);
				lchild->Delete(l, mid);
				rchild->Delete(mid, r);
			}
		}
	private:
		SegmentTreeNode(int l = 0, int r = 0, int c = 0, SegmentTreeNode* lc = nullptr, SegmentTreeNode* rc = nullptr)
		{
			left = l;
			right = r;
			cover = c;
			lchild = lc;
			rchild = rc;
		}
	};

	
}
