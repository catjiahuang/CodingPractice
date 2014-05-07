#ifndef __FlattenTreeToList_h__
#define __FlattenTreeToList_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <stack>

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
	/*
    void flatten(TreeNode *root) {
        if (root == NULL)
            return;
        stack <TreeNode*> st;
        st.push(root);
        TreeNode* lastnd = NULL;
        while(!st.empty()) {
            TreeNode* nd = st.top();
            st.pop();
            if (nd->right) st.push(nd->right);
            if (nd->left) st.push(nd->left);
            if (lastnd) {
                lastnd->right = nd;
                nd->left = NULL;
            }
            lastnd = nd;
        }
    }
	*/

	/*TreeNode* flattenHelper(TreeNode *root) {
        TreeNode *lt = NULL, *rt = NULL;
        if (root->left) lt = flattenHelper(root->left);
        if (root->right) rt = flattenHelper(root->right);
        if (root->left && root->right) {
			// make left child point to left child first
			lt->right = root->right;
            root->right->left = lt;
			// make root point to left child
            root->right = root->left;
            root->left->left = root;
            return rt;
        }
        else if (root->left && root->right == NULL) {
            root->right = root->left;
            root->left->left = root;
            return lt;
        }
        else if (root->left == NULL && root->right) {
            root->right = root->right;
            root->right->left = root;
            return rt;
        }
        else
            return root;
    }
    
    void flatten(TreeNode *root) {
        if (root == NULL)
            return;
        flattenHelper(root);
    }*/
	
	void flatten(TreeNode *root) {
		if (root == NULL) return;

		TreeNode *left = root->left;
		TreeNode *right = root->right;
		
		if (left) {
			root->right = left;
			root->left = NULL;

			TreeNode *rightmost = left;
			while (rightmost->right) rightmost = rightmost->right;
			rightmost->right = right;
		}

		flatten(root->right);
	}
};

class CFlattenTreeToList: public BasicQue {
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
		nodes[1]->right = nodes[2];
		Solution sln;
		sln.flatten(nodes[1]);

		int p = 0;
	}
};

#endif