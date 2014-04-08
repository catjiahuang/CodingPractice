#ifndef __CloneGraph_h__
#define __CloneGraph_h__

#include "BasicQue.h"
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct Node {
	vector<Node*> neighbors;
};

typedef map<Node*, Node*> NodeMap;

class CCloneGraph: public BasicQue {
public:
	void doWork() {
	}
	void CloneGraph(Node* root) {
		NodeMap nMap;
		nMap[root] = newRoot;
		queue <Node*> nQue;
		nQue.push(root);
		Node* newRoot = new Node();

		while (!nQue.empty()) {
			Node* node = nQue.front;
			nQue.pop();
			for (int i = 0; i < node->neighbors.size(); ++i) {
				Node* neighbor = node->neighbors[i];
				if (nMap.find(neighbor) == nMap.end()) {
					Node* newNode = new Node();
					nMap[neighbor] = newNode;
					nMap[node]->neighbors.push_back(newNode);
					nQue.push(neigbhor);
				}
				else {
					nMap[node]->neighbors.push_back(nMap[neighbor]);
				}
			}
		}
		return newRoot;
	}
};

#endif