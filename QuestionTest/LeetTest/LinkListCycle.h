#ifndef __LinkListCycle_h__
#define __LinkListCycle_h__

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
    bool hasCycle(ListNode *head) {
		if (head == NULL)
			return false;
        ListNode* fast = head;
		ListNode* slow = head;
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow) {
				return true;
			}
		}
		return false;
    }
	// a = (n-1)r + (L - a - x);
	ListNode *detectCycle(ListNode *head) {
        if (head == NULL)
			return NULL;
        ListNode* fast = head;
		ListNode* slow = head;
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow) {
				break;
			}
		}
		if (fast->next && fast->next->next) { // if there is a cycle
			ListNode *start = head;
			while (fast != start) {
				start = start->next;
				fast = fast->next;
			}
			return start;
		}
		return NULL;
    }
};

class CLinkListCycle: public BasicQue {
public:
	void doWork() {
		vector <ListNode*> ln;
		for (int i = 0; i < 5; ++i) {
			ln.push_back(new ListNode(i));
		}
		ln[0]->next = ln[1];
		ln[1]->next = ln[2];
		ln[2]->next = ln[3];
		ln[3]->next = ln[4];
		ln[4]->next = ln[2];
		
		Solution s;
		cout << s.detectCycle(ln[0])->val;//s.hasCycle(ln[0]);
	}
};

#endif