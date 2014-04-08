#ifndef __CloneGraph2_h__
#define __CloneGraph2_h__

#include "BasicQue.h"
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};

typedef map <UndirectedGraphNode*, UndirectedGraphNode*> NodeMap;

class Solution {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (!node)
			return NULL;

		UndirectedGraphNode* newGraph = new UndirectedGraphNode(node->label);
		NodeMap nMap;
		nMap[node] = newGraph;
		queue <UndirectedGraphNode*> nQue;
		nQue.push(node);
		
		while (!nQue.empty()) {
			UndirectedGraphNode* currNode = nQue.front();
			nQue.pop();
			for (int i = 0; i < currNode->neighbors.size(); ++i) {
				UndirectedGraphNode* neighbor = currNode->neighbors[i];
				if (nMap.find(neighbor) == nMap.end()) {
					UndirectedGraphNode* newNode = new UndirectedGraphNode(neighbor->label);
					nMap[neighbor] = newNode;
					nMap[currNode]->neighbors.push_back(nMap[neighbor]);
					nQue.push(neighbor);
				}
				else {
					nMap[currNode]->neighbors.push_back(nMap[neighbor]);
				}
			}
		}
		return newGraph;
	}
};

class CCloneGraph2: public BasicQue {
public:
	void doWork() {
		vector <UndirectedGraphNode*> ln;
		for (int i = 0; i < 3; ++i)
			ln.push_back(new UndirectedGraphNode(i));
		ln[0]->neighbors.push_back(ln[1]);
		ln[1]->neighbors.push_back(ln[2]);
		ln[2]->neighbors.push_back(ln[2]);
		Solution sol;
		UndirectedGraphNode* res = sol.cloneGraph(ln[0]);
	}
};

#endif