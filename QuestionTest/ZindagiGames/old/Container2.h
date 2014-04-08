///============================================================================
///======	class CContainer
///============================================================================

#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <new>

#define MAX_CONTAINER_SIZE 65536
#define INT_BIT_SIZE 32
#define BIT_ARRAY_NUM MAX_CONTAINER_SIZE/INT_BIT_SIZE

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
		m_pCurr = pBuffer;
		//m_nSetBit = 0;
		memset(m_nSetBit, 0, BIT_ARRAY_NUM * sizeof(int));
		m_nCount = 0;
	}
	~CContainer() {};

	bool checkBitZero(unsigned i) {
		unsigned id = i / INT_BIT_SIZE;
		unsigned offset = i % INT_BIT_SIZE;
		if ((m_nSetBit[id] & (1 << offset)) == 0)
			return true;
		return false;
	}

	void setBit(unsigned i) {
		unsigned id = i / INT_BIT_SIZE;
		unsigned offset = i % INT_BIT_SIZE;
		m_nSetBit[id] |= 1 << offset;
	}

	void clearBit(unsigned i) {
		unsigned id = i / INT_BIT_SIZE;
		unsigned offset = i % INT_BIT_SIZE;
		m_nSetBit[id] &= ~(1 << offset);
	}

	///======	Adds an element to the container, constructs it and returns it to the caller.
	T *	Add() {
		/*if (m_nIndex == m_nBufferSize)
			Remove((T*)m_pBuffer); // remove the first element;
		T* elem = (T*)m_pCurr;
		m_pCurr += m_nTSize;
		m_nIndex++;
		m_setBit |= 1 << m_nIndex; // set the bit
		return elem;*/
		if (IsFull())
			return NULL;
		for (unsigned i = 0; i < m_nCap; ++i) {
			if (checkBitZero(i)/*(m_nSetBit & (1 << i)) == 0*/) {
				setBit(i);//m_nSetBit |= 1 << i;
				//T* elem = (T*)(m_pBuffer + i * m_nTSize);
				T* elem = new(m_pBuffer + i * m_nTSize) T();
				m_nCount++;
				return elem;
			}
		}
		return NULL; // shouldn't get here
	}
	///======	Note that the return address needs to be persistent during the lifetime of the object.

	///======	Removes an object from the container.
	void Remove(T *elem) {
		// find the object
		char* tmp = m_pBuffer; // start searching from the beginning
		bool found = false;
		unsigned i = 0;
		for (; i < m_nCap; i++) {
			if (tmp == (char*)elem) {
				found = true;
				break;
			}
			tmp += m_nTSize;
		}
		/*// copy up all the afterwards objects
		if (found) {
			for (; i < m_nCap - 1 && i < m_nIndex - 1; i++) {
				char *next = tmp + m_nTSize;
				Copy(tmp, next);
				tmp = next;
			}
			m_nIndex--;
			m_pCurr = tmp;
		}*/
		if (found) {
			clearBit(i);//m_nSetBit &= ~(1 << i); // clean the bit
			elem->~T();
			m_nCount--;
		}
	}

	/*bool Equal(char *e1, char *e2) {
		for (unsigned i = 0; i < m_nTSize; ++i) {
			if (e1[i] != e2[i])
				return false;
		}
		return true;
	}*/

	/*void Copy(char *e_to, char *e_fr) {
		for (unsigned i = 0; i < m_nTSize; ++i) {
			e_to[i] = e_fr[i];
		}
	}*/

	///======	Number of elements currently in the container.
	unsigned Count() const {
		/*int c = 0;
		for (int i = 0; i < Capacity()/INT_BIT_SIZE + 1; ++i) {
			int tmp = m_nSetBit[i];
			while (tmp != 0) {
				tmp = tmp & (tmp -1);
				c++;
			}
		}
		return c;*/
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
		return (Count() == m_nCap ? true : false);
	}		

	///======	Returns the n th element of the container [0..Count -1].
	T const * operator [] (unsigned nIndex) const {
		/*if (nIndex >= m_nCap)
			return NULL; // or trigger an exception;
		return const (T*)(m_pBuffer + nIndex * m_nTSize);*/
		int c = Capacity();
		int id = 0;
		unsigned i = 0;
		for (; i < c; ++i) {
			if (checkBitZero(i) == false/*(m_nSetBit & (1 << i)) != 0*/) {
				if (id == nIndex)
					break;
				id++;
			}
		}
		return const (T*)(m_pBuffer + i * m_nTSize);
	}

	///======	Returns the n th element of the container [0..Count -1].
	T *	operator [] (unsigned nIndex) {
		/*if ((m_nSetBit & (1 << nIndex)) == 0)
			return NULL;
		return (T*)(m_pBuffer + nIndex * m_nTSize);*/
		unsigned c = Capacity();
		int id = 0;
		unsigned i = 0;
		for (; i < c; ++i) {
			if (checkBitZero(i) == false/*(m_nSetBit & (1 << i)) != 0*/) {
				if (id == nIndex)
					break;
				id++;
			}
		}
		return (T*)(m_pBuffer + i * m_nTSize);
	}

#ifdef _ADVANCED
	///======	Sort the elements using a function pointer for the comparison.
	void Sort(int (* Compare)(T const * pX, T const * pY)) {
		
	}
#endif

private:
	char* m_pBuffer;
	unsigned m_nBufferSize;
	//unsigned m_nIndex;
	unsigned m_nTSize;
	char* m_pCurr;
	unsigned m_nCap;
	int m_nSetBit[BIT_ARRAY_NUM]; // only work for buffer size of 32
	unsigned m_nCount;
	int m_nRemap[BIT_ARRAY_NUM]; // record sorted order
};