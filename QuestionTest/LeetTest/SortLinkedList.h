#ifndef __SortLinkedList_h__
#define __SortLinkedList_h__

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
    ListNode *sortList(ListNode *head) {
        ListNode* p = head;
		int n = 0;
		while (p) {
			p = p->next;
			n++;
		}
		return sortListWork(head, n);
    }
	ListNode *sortListWork(ListNode *head, int num) {
		if (num == 0 || num == 1)
			return head;
		int i = 0;
		ListNode *head2 = head;
		int n1 = num / 2, n2 = num - n1;
		while (i < n1) {
			head2 = head2->next;
			i++;
		}
		head = sortListWork(head, n1);
		head2 = sortListWork(head2, n2);
		int p = 0, q = 0;
		ListNode* newHead = new ListNode(0); // just a head
		ListNode* res = newHead;
		while (p < n1 || q < n2) {
			if (p >= n1) {
				newHead->next = head2;
				while (q < n2) {
					newHead = newHead->next;
					q++;
				}
				break;
			}
			else if (q >= n2) {
				newHead->next = head;
				while (p < n1) {
					newHead = newHead->next;
					p++;
				}
				break;
			}
			else {
				if (head->val < head2->val) {
					newHead->next = head;
					newHead = newHead->next;
					head = head->next;
					p++;
				}
				else {
					newHead->next = head2;
					newHead = newHead->next;
					head2 = head2->next;
					q++;
				}
			}
		}
		newHead->next = NULL;

		ListNode* headNode = res;
		res = res->next;
		delete headNode;
		
		return res;
	}
};

class CSortLinkedList: public BasicQue {
public:
	void doWork() {
		vector <ListNode*> ln;
		for (int i = 0; i < 4; ++i) {
			ln.push_back(new ListNode(i));	
		}
		ln[3]->next = ln[2];
		ln[2]->next = ln[1];
		ln[1]->next = ln[0];

		Solution s;
		ListNode* res = s.sortList(ln[3]);
		while (res) {
			cout << res->val << " ";
			res = res->next;
		}
	}
};

#endif