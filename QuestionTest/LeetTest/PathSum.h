#ifndef __PathSum_h__
#define __PathSum_h__

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
    // problem 1
	bool hasPathSumHelper(TreeNode *root, int curr, int sum) {
        if (root == NULL)
            if (curr == sum) return true;
            else return false;
        curr += root->val;
        bool lres = hasPathSumHelper(root->left, curr, sum),
            rres = hasPathSumHelper(root->right, curr, sum);
		if (root->left && root->right) {
			if (lres || rres) return true;}
		else if (root->left) {
			if (lres) return true;}
		else if (root->right) {
			if (rres) return true;}
		else {
			if (curr == sum) return true;}
        return false;

		// writing style 2
		/*curr += root->val;
		if (root ->left && root->right) {
			if (hasPathSumHelper(root->left, curr, sum) ||
				hasPathSumHelper(root->right, curr, sum))
			return true;
		}
		else if (root->left) {
			if (hasPathSumHelper(root->left, curr, sum)) return true;
		}
		else if (root->right) {
			if (hasPathSumHelper(root->right, curr, sum)) return true;
		}
		else {
			if (curr == sum) return true;
		}
		return false;
		*/

    }

    bool hasPathSum(TreeNode *root, int sum) {
        if (root == NULL)
            return false;
        return hasPathSumHelper(root, 0, sum);
    }

	// problem 2
	void pathSumHelper(TreeNode *root, int sum, int curr, vector<int> path, vector<vector<int>> &allPath) {
		curr += root->val;
		path.push_back(root->val);
		if (root->left) pathSumHelper(root->left, sum, curr, path, allPath);
		if (root->right) pathSumHelper(root->right, sum, curr, path, allPath);
		if (!root->left && !root->right) {
			if (curr == sum) allPath.push_back(path);
		}
		return;
	}

	vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int>> allPath;
		if (root == NULL)
			return allPath;
		vector<int> path;
		pathSumHelper(root, sum, 0, path, allPath);
		return allPath;
    }
};

class CPathSum: public BasicQue {
public:
	void doWork() {
		vector <TreeNode*> nodes;
		for (int i = 0; i <= 6; ++i)
			nodes.push_back(new TreeNode(i));
		//nodes[1]->left = nodes[2];
		//nodes[1]->right = nodes[5];
		//nodes[2]->left = nodes[3];
		//nodes[2]->right = nodes[4];
		//nodes[5]->right = nodes[6];
		Solution sln;
		cout << sln.hasPathSum(nodes[1], 1);
	}
};

#endif