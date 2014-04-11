#ifndef __SurrReg_h__
#define __SurrReg_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void solve(vector<vector<char>> &board) {
		if (board.size() == 0 || board.front().size() == 0)
			return;
		// scan 4 edges, store all Os
		int m = board.size(), n = board.front().size();
		vector<int> xIds, yIds; 
		for (int i = 0; i < m; ++i) {
			if (board[i][0] == 'O') {
				xIds.push_back(i);
				yIds.push_back(0);
			}
			if (board[i][n-1] == 'O') {
				xIds.push_back(i);
				yIds.push_back(n-1);
			}
		}
		for (int j = 0; j < n ; ++j) {
			if (board[0][j] == 'O') {
				xIds.push_back(0);
				yIds.push_back(j);
			}
			if (board[m-1][j] == 'O') {
				xIds.push_back(m-1);
				yIds.push_back(j);
			}
		}
		// do BFS on stored Os, mark O to Y
		for (int k = 0; k < xIds.size(); ++k) {
			int x = xIds[k], y = yIds[k];
			board[x][y] = 'Y';
			if (x > 0 && board[x-1][y] == 'O') {
				xIds.push_back(x-1);
				yIds.push_back(y);
			}
			if (x < m-1 && board[x+1][y] == 'O') {
				xIds.push_back(x+1);
				yIds.push_back(y);
			}
			if (y > 0 && board[x][y-1] == 'O') {
				xIds.push_back(x);
				yIds.push_back(y-1);
			}
			if (y < n-1 && board[x][y+1] == 'O') {
				xIds.push_back(x);
				yIds.push_back(y+1);
			}
		}
		// scan whole board, mark O to X, Y to O
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (board[i][j] == 'O')
					board[i][j] = 'X';
				else if (board[i][j] == 'Y')
					board[i][j] = 'O';
			}
		}
	}
};

class CSurrReg: public BasicQue {
public:
	void doWork() {
		vector<vector<char>> board;
		int m = 4,
			n = 4;//6;//4;
		board.resize(m);
		char vals[] = "XXXXXOOXXXOXXOXX";
		//char vals[] = "XOXOXOOXOXOXXOXOXOOXOXOX";
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j)
				board[i].push_back(vals[i*n+j]);
		}
		Solution sln;
		sln.solve(board);
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j)
				cout << board[i][j] << " ";
			cout << endl;
		}
	}
};

#endif