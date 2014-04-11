#ifndef __SumRootLeaf_h__
#define __SumRootLeaf_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>

using namespace std;


//Definition for binary tree
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int sumNumbers(TreeNode *root) {
		return sumNumbersHelper(root, 0);
    }
	int sumNumbersHelper(TreeNode *root, int val) {
		if (root == NULL)
			return val;
		val = val*10 + root->val;
		if (root->left && root->right)
			return sumNumbersHelper(root->left, val) + sumNumbersHelper(root->right, val);
		else if (root->left)
			return sumNumbersHelper(root->left, val);
		else if (root->right)
			return sumNumbersHelper(root->right, val);
		else
			return val;
	}
};

class CSumRootLeaf: public BasicQue {
public:
	void doWork() {
		vector<TreeNode*> vNodes;
		for (int i = 0; i <= 4; ++i) {
			vNodes.push_back(new TreeNode(i));
		}
		vNodes[1]->left = vNodes[2];
		vNodes[1]->right = vNodes[3];
		vNodes[3]->right = vNodes[4];
		Solution sln;
		cout << sln.sumNumbers(vNodes[1]);
	}
};

#endif