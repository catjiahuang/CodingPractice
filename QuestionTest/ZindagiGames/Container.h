///============================================================================
///======	class CContainer
///============================================================================

#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <new>

#define _ADVANCED

#define MAX_CONTAINER_SIZE 65536

/*
	We divide the buffer into consecutive blocks of the size of T (m_nTSize), and index them
	m_nRemap records the mapping from the sorted indices to the actual indices in the buffer,
	e.g. m_nRemap[2] = 7 means the block of sorted index 2 is actually located at index 7 in the buffer.
	It also records whehter a block is taken or not. e.g. m_nRemap[i] = -1 means the block of index 7 in the buffer is not taken,
	when we sort the array, we only change the mapping from sorted order to the actual order in the buffer, so it can satisfy the sanity check in the test.
	The non-taken blocks will not paticipate in the sorting.

	Time complexity for Add and Remove is O(N), Sort is O(N^2), N is the capacity of the container
	Test on my computer (Xeon 3.33GHz):
	gs_nBufferSize = 25, nNumAllocs = 20000000: 16 secs
	gs_nBufferSize = 100, nNumAllocs = 20000000: 24 secs
	gs_nBufferSize = 1000, nNumAllocs = 20000000: 115 secs
	gs_nBufferSize = 2000, nNumAllocs = 20000000: 214 secs

*/

template<typename T>
class CContainer
{
public:
	///======	Constructs the container from a pre-defined buffer.
	CContainer(char * pBuffer, unsigned nBufferSize) {
		m_pBuffer = pBuffer;
		m_nBufferSize = nBufferSize;
		m_nTSize = sizeof(T)/sizeof(char);
		m_nCap = m_nBufferSize / m_nTSize;
		m_nCount = 0;
		memset(m_nRemap, -1, sizeof(m_nRemap));
	}
	~CContainer() {};
	
	///======	Adds an element to the container, constructs it and returns it to the caller.
	T *	Add() {
		T* elem = NULL;
		for (unsigned i = 0; i < Capacity(); ++i) {
			if (m_nRemap[i] == -1) {
				elem = new(m_pBuffer + i * m_nTSize) T();
				m_nRemap[i] = i;
				m_nCount++;
				break;
			}
		}
		assert(elem != NULL); // cannot add, the container is full
		return elem;
	}
	///======	Note that the return address needs to be persistent during the lifetime of the object.

	///======	Removes an object from the container.
	void Remove(T *elem) {
		// search for the element
		char* tmp = m_pBuffer;
		unsigned i = 0;
		for (; i < Capacity(); ++i) {
			if (tmp == (char*)elem) {
				break;
			}
			tmp += m_nTSize;
		}
		if (i < Capacity()) { // found the element, remove it
			elem->~T();
			for (unsigned j = 0; j < Capacity(); ++j) {
				if (m_nRemap[j] == i)
					m_nRemap[j] = -1;
			}
			m_nCount--;
		}
	}

	///======	Number of elements currently in the container.
	unsigned Count() const {
		return m_nCount;
	}

	///======	Max number of elements the container can contain. You can limit the capacity to 65536 elements if this makes your implementation easier.
	unsigned Capacity() const {
		return m_nCap;
	}

	///======	Is container empty?
	bool IsEmpty() const {
		return (Count() == 0 ? true : false);
	}

	///======	Is container full?
	bool IsFull() const {
		return (Count() == Capacity() ? true : false);
	}		

private:
	// Get the element provided with the actual index in the buffer
	T* Get(unsigned nIndex) {
		return (T*)(m_pBuffer + nIndex * m_nTSize);
	}

	// Get the element provided with the mapped (sorted) index accessed by outside
	T* GetMapped(unsigned nIndex) {
		int id = 0;
		unsigned i = 0;
		for (; i < Capacity(); ++i) { // find the nIndex th element that is taken (not -1)
			if (m_nRemap[i] != -1) {
				if (id == nIndex)
					break;
				id++;
			}
		}
		return Get(m_nRemap[i]); // use the actual index to retrive the element in the buffer
	}

public:
	///======	Returns the n th element of the container [0..Count -1].
	T const * operator [] (unsigned nIndex) const {
		return const GetMapped(nIndex);
	}

	///======	Returns the n th element of the container [0..Count -1].
	T *	operator [] (unsigned nIndex) {
		return GetMapped(nIndex);
	}

#ifdef _ADVANCED
	///======	Sort the elements using a function pointer for the comparison.
	// Since memory allocation is not allowed in the instruciton, 
	// I can only adopt the O(N^2) time complexity sorting algorithms
	void Sort(int (* Compare)(T const * pX, T const * pY)) {
		for (unsigned i = 0; i < Count(); ++i) {
			unsigned j = 0;
			for (; j < Capacity() - 1; ++j) {
				if (m_nRemap[j] != -1) // find a taken block
					break;
			}
			for (unsigned k = j + 1; k < Capacity(); ++k) {
				if (m_nRemap[k] == -1) // find the subsequent taken block
					continue;
				if (Compare(Get(m_nRemap[j]), Get(m_nRemap[k])) == 1) {
					// swap the mapped indices
					m_nRemap[j] ^= m_nRemap[k];
					m_nRemap[k] ^= m_nRemap[j];
					m_nRemap[j] ^= m_nRemap[k];
				}
				j = k;
			}
		}
	}
#endif

private:
	char* m_pBuffer;
	unsigned m_nBufferSize;
	unsigned m_nTSize; // the size of T
	unsigned m_nCap; // max number of elements that the container can contain
	unsigned m_nCount; // current number of elements in the container
	int m_nRemap[MAX_CONTAINER_SIZE]; // record the mapping from sorted indices to actual indices in the buffer
};