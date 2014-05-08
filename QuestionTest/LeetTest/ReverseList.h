#ifndef __ReverseList_h__
#define __ReverseList_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        if (head == NULL)
            return NULL;
        if (n - m > 0) {
            ListNode *p = head, *p1 = NULL;
            int i = 1;
            while(i < m) {
                p1 = p;
                p = p->next;
                i++;
            }
            ListNode *tmp = NULL, *prev = NULL, *start = p;
            while(i <= n) {
                tmp = p->next;
                p->next = prev;
                prev = p;
                p = tmp;
                i++;
            }
            if (p1) p1->next = prev; // connect new head
            start->next = tmp; // connect new tail
            if (p1 == NULL) head = prev;
        }
        return head;
    }
};

class CReverseList: public BasicQue {
public:
	void doWork() {
		vector <ListNode*> nds;
		for (int i = 0; i <= 5; ++i)
			nds.push_back(new ListNode(i));
		//nds[3]->next = nds[5];
		nds[1]->next = nds[2];
		nds[2]->next = nds[3];
		nds[3]->next = nds[4];
		nds[4]->next = nds[5];
		Solution sln;
		//sln.reverseBetween(nds[3],1,2);
		sln.reverseBetween(nds[1],2,4);
	}
};

#endif