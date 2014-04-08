#ifndef __CopyListRandPointer_h__
#define __CopyListRandPointer_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std::tr1;

struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
		if (head == NULL)
			return NULL;
		RandomListNode *res = new RandomListNode(head->label);
		RandomListNode *p = res;
		unordered_map <RandomListNode*, RandomListNode*> nMap;
		while (head) {
			if (head->next) {
				if (nMap.find(head->next) == nMap.end()) {
					p->next = new RandomListNode(head->next->label);
					nMap[head->next] = p->next;
				}
				else
					p->next = nMap[head->next];
			}

			if (head->random) {
				if (nMap.find(head->random) == nMap.end()) {
					p->random = new RandomListNode(head->random->label);
					nMap[head->random] = p->random;
				}
				else
					p->random = nMap[head->random];
			}
			p = p->next;
			head = head->next;
		}
		return res;
    }
};

class CCopyListRandPointers: public BasicQue {
public:
	void doWork() {
		
	}
};


#endif