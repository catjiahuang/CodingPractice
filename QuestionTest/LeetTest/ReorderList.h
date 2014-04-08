#ifndef __BasicQueExp_h__
#define __BasicQueExp_h__

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
    void reorderList(ListNode *head) {
        if (head == NULL)
			return;
		int n = 0;
		ListNode *tmp = head;
		while (tmp) {
			n++;
			tmp = tmp->next;
		}
		int i = 0;
		tmp = head;
		ListNode* tail = head;
		while (i < n - (n - 1)/2) {
			i++;
			tail = tmp;
			tmp = tmp->next;
		}
		tail->next = NULL;

		// reverse the second list
		if (tmp) {
			ListNode* last = tmp;
			tmp = tmp->next;
			last->next = NULL;
			while(tmp) {
				ListNode *next = tmp->next;
				tmp->next = last;
				last = tmp;
				tmp = next;
			}
			tmp = last;
		}

		ListNode *head2 = head;
		while (tmp) {
			ListNode *next = head2->next;
			head2->next = tmp;
			ListNode *tmpNext = tmp->next;
			tmp->next = next;
			head2 = next;
			tmp = tmpNext;
		}
    }
};


class CReorderList: public BasicQue {
public:
	void doWork() {
		Solution s;
		vector <ListNode*> ln;
		for(int i = 0; i < 7; i++)
			ln.push_back(new ListNode(i));
		ln[1]->next = ln[2];
		ln[2]->next = ln[3];
		ln[3]->next = ln[4];
		ln[4]->next = ln[5];
		ln[5]->next = ln[6];

		ListNode *res = ln[1];
		s.reorderList(res);
		while(res) {
			cout << res->val << " ";
			res = res->next;
		}
	}
};

#endif