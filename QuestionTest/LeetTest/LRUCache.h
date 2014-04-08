#ifndef __LRUCache_h__
#define __LRUCache_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <map>

using namespace std;

//typedef pair<int, int> CacheElem;
//typedef vector <CacheElem> CacheType;



struct MyListNode {
	int val;
	int key;
	MyListNode *next;
	MyListNode *prev;
	MyListNode(int k, int v): key(k), val(v), prev(NULL), next(NULL) {}
};

struct LinkList {
	MyListNode *head;
	MyListNode *tail;
	LinkList() {
		head = NULL;
		tail = NULL;
	}
	void removeNode(MyListNode* node) {
		if (node->prev) {
			node->prev->next = node->next;
			if (node->next)
				node->next->prev = node->prev;
			else
				tail = node->prev;
		}
		else {
			head = node->next;
		}
		node->prev = NULL;
		node->next = NULL;
	}
	void insertFront(MyListNode* node) {
		node->next = head;
		if (head)
			head->prev = node;
		head = node;
		if (head->next == NULL)
			tail = head;
	}
	void deleteLast() {
		MyListNode* delNode = tail;
		tail = tail->prev;
		if (tail)
			tail->next = NULL;
		delete delNode;
	}
};

class LRUCache{
public:
	LRUCache(int capacity) {
		mCap = capacity;
	}
    
	int get(int key) {
		if (mMap.find(key) != mMap.end()) {
			MyListNode *node = mMap[key];
			mList.removeNode(node);
			mList.insertFront(node);
			return mMap.find(key)->second->val;
		}
		return -1;
	}
     
	void set(int key, int value) {
		if (mMap.find(key) != mMap.end()) {
			MyListNode *node = mMap[key];
			node->val = value;
			mList.removeNode(node);
			mList.insertFront(node);
		}
		else {
			if (mMap.size() == mCap) {
				// remove least recently visited node
				mMap.erase(mList.tail->key);
				mList.deleteLast();
			}
			// add new node
			MyListNode *node = new MyListNode(key, value);
			mList.insertFront(node);
			mMap[key] = node;
		}
	}

	int mCap;
	map <int, MyListNode*> mMap;
	LinkList mList;
};

    /*LRUCache(int capacity) {
		mCache.resize(capacity);
		for (CacheType::iterator it = mCache.begin(); it != mCache.end(); it++) {
			it->first = -1;
			it->second = -1;
		}
		mNum = capacity;
    }
	
	int get(int key) {
		for (CacheType::iterator it = mCache.begin(); it != mCache.end(); it++) {
			if (it->first == key && it->second != -1)
				return it->second;
		}
		return -1;
    }

	void set(int key, int value) {
		CacheType::iterator it = mCache.begin();
		for (; it != mCache.end(); it++) {
			if (it->first == key && it->second != -1) {
				it->second = value;
				break;
			}
		}
		if (it != mCache.end()) {
			CacheElem elem = *it;
			mCache.erase(it);
			mCache.insert(mCache.begin(), elem);
		}
		else {
			mCache.pop_back();
			mCache.insert(mCache.begin(), make_pair(key, value));
		}
    }

	CacheType mCache;
	int mNum;
	*/

class CLRUCache: public BasicQue {
public:
	void doWork() {
		//LRUCache lru(2);
		//lru.set(2,22);
		//lru.set(3,33);
		//lru.set(4,44);
		//cout << lru.get(2);
		//3,[set(1,1),set(2,2),set(3,3),set(4,4),get(4),get(3),get(2),get(1),set(5,5),get(1),get(2),get(3),get(4),get(5)]
		LRUCache lru(3);
		lru.set(1,1);
		lru.set(2,2);
		lru.set(3,3);
		lru.set(4,4);
		cout << lru.get(4) << " ";
		cout << lru.get(3) << " ";
		cout << lru.get(2) << " ";
		cout << lru.get(1) << " ";
		lru.set(5,5);
		cout << lru.get(1) << " ";
		cout << lru.get(2) << " ";
		cout << lru.get(3) << " ";
		cout << lru.get(4) << " ";
		cout << lru.get(5);
	}
};

#endif