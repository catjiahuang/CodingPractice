#ifndef __MaxPtLine_h__
#define __MaxPtLine_h__

#include "BasicQue.h"
#include <vector>
#include <map>
#include <unordered_map>

using namespace std::tr1;

struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
    int maxPoints(vector<Point> &points) {
		int maxNum = 0;
		for (int i = 0; i < points.size(); ++i) {
			map <float, int> numMap;
			numMap[INT_MIN] = 0;
			int duplicate = 1;
			for (int j = 0; j < points.size(); ++j) {
				if (i != j) {
					// duplicate point
					if (points[i].x == points[j].x && points[i].y == points[j].y) {
						duplicate++;
					}
					else {
						float k = (points[i].x == points[j].x) ? INT_MAX : 
							(float)(points[j].y - points[i].y) / (points[i].x - points[j].x);
						numMap[k]++;
					}
				}
			}
			for (map <float, int>::iterator it = numMap.begin(); it != numMap.end(); ++it) {
				if (it->second + duplicate > maxNum)
					maxNum = it->second + duplicate;
			}
		}
		return maxNum;
    }
};

/*int checkSameLine(vector<Point> &points, int accumId, int ptId) {
	
}
map <int, int> ptMap; // node list index to node num
int maxPointsWork(vector<Point> &points, int &accumId, int ptId) {
	if (ptId == points.size()) {
		return ptMap[accumId];
	}
	int id1, id2; // include current node
	// check if current node is on straight line with previous nodes
	int v1 = maxPointsWork(points, id1, ptId + 1);
	int v2 = maxPointsWork(points, id2, ptId + 1);
	if (checkSameLine(points, id1, ptId))
		v1++;
	if (checkSameLine(points, id2, ptId))
		v2++;
	id1 << 1;
	id2 = id1 + 1;
	ptMap[id1] = v1;
	ptMap[id2] = v2;
	if (v1 > v2) {
		accumId = id1;
		return v1;
	}
	else {
		accumId = id2;
		return v2;
	}
}*/

class CMaxPtLine: public BasicQue {
public:
	void doWork() {
		Solution s;
		vector<Point> vp;
		vp.push_back(Point(1,1));
		vp.push_back(Point(2,2));
		vp.push_back(Point(-2,2));
		vp.push_back(Point(5,5));
		cout << s.maxPoints(vp);
		unordered_map<int, int> test;
	}
};

#endif