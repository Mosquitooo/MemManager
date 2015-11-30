
#include"MemTrace.h"
#include<pthread.h>

#ifdef MEMORY_LEAK_CHECK

List MemManager;

void* operator new(size_t size, const char* filename, int line)
{
	if(size == 0)
		size = 1;
	void *p = malloc(size);
	MemManager.Insert(Node(reinterpret_cast<long>(p), filename, line, size));
	return p;
}

void operator delete(void* p)throw()
{
	if(p == NULL) return;
	MemManager.Delete(Node(reinterpret_cast<long>(p)));
	free(p);
}

void* operator new[](size_t size, const char* filename, int line)
{
	if(size == 0) 
		size = 1;
	void *p = malloc(size);
	MemManager.Insert(Node(reinterpret_cast<long>(p), filename, line, size));
	return p;
}

void operator delete[](void* p)throw()
{
	if(p == NULL) return;
	MemManager.Delete(Node(reinterpret_cast<long>(p)));
	free(p);
}

#endif


