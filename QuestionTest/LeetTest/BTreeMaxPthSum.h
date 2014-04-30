#ifndef __BTreeMaxPthSum_h__
#define __BTreeMaxPthSum_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	int maxPathSumHelper(TreeNode *root, int &maxLineSum) {
		if (root == NULL) {
			maxLineSum = 0;
			return 0;
		}
		int lls = 0, rls = 0;
		int lps = maxPathSumHelper(root->left, lls) + (root->left ? 0 : root->val);
		int rps = maxPathSumHelper(root->right, rls) + (root->right ? 0 : root->val);
		int mps = lls > 0 ? (rls > 0 ? lls + rls : lls) : (rls > 0 ? rls : 0);
		mps += root->val;

		int ls = max(lls, rls);
		maxLineSum = (ls > 0 ? ls : 0) + root->val;
		
		return max(max(lps, rps), mps);
	}
    int maxPathSum(TreeNode *root) {
		int maxLineSum = 0;
        return maxPathSumHelper(root, maxLineSum);
    }
};

class CBTreeMaxPthSum: public BasicQue {
public:
	void doWork() {
		vector<TreeNode*> tree;
		for (unsigned int i = 0; i < 6; i++) {
			tree.push_back(new TreeNode(i));
		}
		tree[1]->left = tree[2];
		tree[1]->right = tree[3];
		tree[2]->left = tree[4];
		tree[2]->right = tree[5];
		Solution sln;
		cout << sln.maxPathSum(tree[1]);
	}
};

#endif