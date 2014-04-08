#ifndef __InserSortLinkedList_h__
#define __InserSortLinkedList_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *insertionSortList(ListNode *head) {
        if (head == NULL)
			return head;

		ListNode* currNode = head;

		int len = 0;
		ListNode* tmpNode = head;
		while (tmpNode) {
			len++;
			tmpNode = tmpNode->next;
		}

		int i = 0;
		// it's better to create a new head to prevent case like the last element doesn't need to be moved
		ListNode* newHeadNode = new ListNode(0);
		while (i < len) {
			ListNode* tmpNode = newHeadNode;

			// do the comparing work
			// tmpNode->next is the node we are dealing with now
			while (tmpNode->next && currNode->val > tmpNode->next->val) {
				tmpNode = tmpNode->next;
			}
			// insert currNode between tmpNode and tmpNode->next
			ListNode * nextNode = currNode->next;
			currNode->next = tmpNode->next;
			tmpNode->next = currNode;
			currNode = nextNode;
			i++;
		}

		return newHeadNode->next;
    }
};

class CInserSortLinkedList: public BasicQue {
public:
	void doWork() {
		vector<ListNode*> nl;
		for (int i = 0; i < 5; ++i)
			nl.push_back(new ListNode(i));
		nl[3]->next = nl[4];
		nl[4]->next = nl[1];

		Solution s;
		ListNode* res = s.insertionSortList(nl[3]);

		while (res) {
			cout << res->val << " ";
			res = res->next;
		}
	}
};

#endif