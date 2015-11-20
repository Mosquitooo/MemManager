#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__

#include<assert.h>

#define _DEBUG
#ifdef _DEBUG
	#define ASSERT(exp) assert(exp)
#else
	#define ASSERT(exp)
#endif

template<typename T, int size>
class Array
{
public:
	T& operator[](int index)
	{
		if(index >= size)
		{
			ASSERT(false);
		}
		return *(m_pData + index);
	}
	
public:
	void MemSet()
	{
		
	}
	
	void Memcpy()
	{
		
	}
	
	
public:
	T m_pData[size];
};

#endif
