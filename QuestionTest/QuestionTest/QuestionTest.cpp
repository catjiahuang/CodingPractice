// QuestionTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "BasicQue.h"
//#include "CountBit.h"
//#include "NumOfOnes.h"
//#include "StrRotate.h"
#include "FindMaxK.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//BasicQue* bq = new CCountBit();
	//BasicQue* bq = new CNumOfOnes();
	//BasicQue* bq = new CStrRotate();
	BasicQue* bq = new CFindMaxK();
	bq->doWork();

	cout << endl;
	system("pause");
	return 0;
}