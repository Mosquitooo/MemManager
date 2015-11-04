
#include"MemTrace.h"

MemTrace MemManager;

void* operator new(size_t size, const char* filename, int line)
{
	void *p = malloc(size);
	MemManager.m_MemList.Insert(Node(reinterpret_cast<long>(p), filename, line));
	return p;
}

void operator delete(void* p)throw()
{
	MemManager.m_MemList.Delete(Node(reinterpret_cast<long>(p)));
	free(p);
}

void* operator new[](size_t size, const char* filename, int line)
{
	void *p = malloc(size);
	MemManager.m_MemList.Insert(Node(reinterpret_cast<long>(p), filename, line));
	return p;
}

void operator delete[](void* p)throw()
{
	MemManager.m_MemList.Delete(Node(reinterpret_cast<long>(p)));
	free(p);
}

MemTrace::MemTrace()
{

}

MemTrace::~MemTrace()
{
	m_MemList.PrintList();
}


