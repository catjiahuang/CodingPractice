#ifndef __StrRotate_h__
#define __StrRotate_h__

#include "BasicQue.h"

class CStrRotate: public BasicQue {
public:
	void doWork() {
		char src[] = "AABCD";//"ABCD";//
		char des[] = "CDAA";//"ACBD";//
		cout << StrRotate2(src, des, strlen(src), strlen(des));
	}
	bool StrRotate(char *src, char *des, int s_l, int d_l) {
		if (s_l == 0 || d_l == 0)
			return false;
		int rot_n = 0;
		while (rot_n < s_l) {
			int tmp = src[0];
			for (int i = 0; i < s_l - 1; ++i) {
				src[i] = src[i + 1];
			}
			src[s_l - 1] = tmp;
			if (strstr(src, des))
				return true;
			rot_n++;
		}
		return false;
	}
	bool StrRotate2(char *src, char *des, int s_l, int d_l) {
		char *new_s = (char*)malloc((s_l * 2 + 1) * sizeof(char));
		memset(new_s, 0, (s_l * 2 + 1) * sizeof(char));
		strcat(new_s, src);
		strcat(new_s, src);
		if (strstr(new_s, des))
			return true;
		return false;
	}
};

#endif