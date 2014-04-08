#ifndef __PostOrderTrav_h__
#define __PostOrderTrav_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector <int> res;
		potWork(root, res);
		return res;
    }
	void potWork(TreeNode *root, vector<int> &res) {
		if (root == NULL)
			return;
		potWork(root->left, res);
		potWork(root->right, res);
		res.push_back(root->val);
	}
	vector<int> preorderTraversal(TreeNode *root) {
		vector <int> res;
		preoWork(root, res);
		return res;
    }
	void preoWork(TreeNode *root, vector<int> &res) {
		if (root == NULL)
			return;
		res.push_back(root->val);
		preoWork(root->left, res);
		preoWork(root->right, res);
	}
	// method 2
	vector<int> postorderTraversal2(TreeNode *root) {
		vector <int> res;
		if (root == NULL)
			return res;
		stack <TreeNode*> nStack;
		nStack.push(root);
		while (!nStack.empty()) {
			if (root->right)
				nStack.push(root->right);
			else if (root->left)
				nStack.push(root->left);
			else {
				res.push_back(nStack.top()->val);
				nStack.pop();
			}
		}
		return res;
	}
};

class CPostOrderTrav: public BasicQue {
public:
	void doWork() {
		
	}
};

#endif