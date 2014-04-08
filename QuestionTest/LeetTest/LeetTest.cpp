// LeetTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "BasicQue.h"
//#include "CloneGraph2.h"
//#include "EvaExp.h"
//#include "MaxPtLine.h"
//#include "SortLinkedList.h"
//#include "InserSortLinkedList.h"
//#include "LRUCache.h"
//#include "ReorderList.h"
//#include "LinkListCycle.h"
//#include "WordBreak.h"
//#include "CopyListRandPointer.h"
//#include "Candy.h"
//#include "GasStation.h"
//#include "PalDroParti.h"
#include "ReverseStr.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//new CLinkListCycle();//new CReorderList();//CLRUCache();//CInserSortLinkedList();//CSortLinkedList();//CMaxPtLine();
	BasicQue* bq = new CReverseStr();//new CPalDroParti();//new CGasStation();//new CWordBreak();
	bq->doWork();

	cout << endl;
	system("pause");
	return 0;
}