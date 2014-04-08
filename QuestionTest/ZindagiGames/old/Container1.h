///============================================================================
///======	class CContainer
///============================================================================

#include <cstdlib>
#include <cassert>
#include <ctime>


template<typename T>
class CContainer
{
public:
	///======	Constructs the container from a pre-defined buffer.
	CContainer(char * pBuffer, unsigned nBufferSize) {
		m_pBuffer = pBuffer;
		m_nBufferSize = nBufferSize;
		m_nIndex = 0;
		m_nTSize = sizeof(T)/sizeof(char);
		m_pHead = pBuffer;
	}
	~CContainer() {};

	///======	Adds an element to the container, constructs it and returns it to the caller.
	T *	Add() {
		if (m_nIndex + m_nTSize > m_nBufferSize) {
			m_pHead = m_pBuffer;
			m_nIndex = 0;
		}
		T* elem = (T*)m_pHead;
		m_pHead += m_nTSize;
		m_nIndex += m_nTSize;
		return elem;
	}
	///======	Note that the return address needs to be persistent during the lifetime of the object.

	///======	Removes an object from the container.
	void Remove(T *) {
		
	}

	///======	Number of elements currently in the container.
	unsigned Count() const {
	
	}

	///======	Max number of elements the container can contain. You can limit the capacity to 65536 elements if this makes your implementation easier.
	unsigned Capacity() const {
	
	}

	///======	Is container empty?
	bool IsEmpty() const {
	
	}

	///======	Is container full?
	bool IsFull() const {
		
	}		

	///======	Returns the n th element of the container [0..Count -1].
	T const * operator [] (unsigned nIndex) const {
	
	}

	///======	Returns the n th element of the container [0..Count -1].
	T *	operator [] (unsigned nIndex) {
	
	}

#ifdef _ADVANCED
	///======	Sort the elements using a function pointer for the comparison.
	void Sort(int (* Compare)(T const * pX, T const * pY)) {
		
	}
#endif

private:
	char* m_pBuffer;
	unsigned m_nBufferSize;
	int m_nIndex;
	int m_nTSize;
	char* m_pHead;
};
