#ifndef __FindMaxK_h__
#define __FindMaxK_h__

#include "BasicQue.h"

class CFindMaxK: public BasicQue {
public:
	void doWork() {
		int data[] = {3, 2, 9, 11, 1, 7};//{3, 5, 2, 1, 4};//
		int len = sizeof(data) / sizeof(int);
		//bubbleSort(data, len);
		//insertSort(data, len);
		//mergeSort(data, len);
		quickSort(data, len);
		for (int i = 0; i < len; ++i)
			cout << data[i] << " "; 
	}
	// Bubble sort
	void bubbleSort (int data[], int len) {
		for (int i = 0; i < len - 1; ++i) {
			for (int j = 0; j < (len - i - 1); ++j) {
				if (data[j] > data[j+1])
					swap(data[j], data[j+1]);
			}
		}
	}
	// Insertion sort
	void insertSort(int data[], int len) {
		for (int i = 0; i < len; ++i) {
			int j = i;
			for (; j > 0; --j) {
				if (data[i] > data[j-1]) {
					break;
				}
			}
			swap(data[i], data[j]);
			for (int k = j + 1; k < i; k++) {
				swap(data[k], data[i]);
			}
		}
	}
	// Merge sort: recursion
	void mergeSort(int data[], int len) {
		if (len <= 1)
			return;
		int mid_i = len/2;
		int l_len = mid_i, r_len = len - mid_i;
		int* l_data = (int *)malloc(l_len * sizeof(int));
		int* r_data = (int *)malloc(r_len * sizeof(int));
		memcpy(l_data, data, l_len * sizeof(int));
		memcpy(r_data, data + l_len, r_len * sizeof(int));
		mergeSort(l_data, l_len);
		mergeSort(r_data, r_len);
		int l_i = 0, r_i = 0, res_i = 0;
		while (res_i < len) {
			if (l_i == l_len) {
				data[res_i] = r_data[r_i];
				r_i++;
			}
			else if (r_i == r_len) {
				data[res_i] = l_data[l_i];
				l_i++;
			}
			else if (l_data[l_i] < r_data[r_i]) {
				data[res_i] = l_data[l_i];
				l_i++;
			}
			else {
				data[res_i] = r_data[r_i];
				r_i++;
			}
			res_i++;
		}
		free(l_data);
		free(r_data);
	}
	// Heap sort
	void heapSort(int data[], int len) {
		//
	}
	// Quick sort: recursion
	void quickSort(int data[], int len) {
		if (len <= 1)
			return;
		int mid_v = data[len/2];
		int *l_data = (int*)malloc(len * sizeof(int)), 
			*r_data = (int*)malloc(len * sizeof(int));
		int l_i = 0, r_i = 0;
		for (int i = 0; i < len; ++i) {
			if (data[i] != mid_v) // easily missed condition!
				if (data[i] < mid_v) {
					l_data[l_i] = data[i];
					l_i++;
				}
				else {
					r_data[r_i] = data[i];
					r_i++;
				}
		}
		quickSort(l_data, l_i);
		quickSort(r_data, r_i);
		memcpy(data, l_data, l_i * sizeof(int));
		data[l_i] = mid_v;
		memcpy(data + l_i + 1, r_data, r_i * sizeof(int));
		free(l_data);
		free(r_data);
	}
};

#endif