
#ifndef __MEMTRACE_H__
#define __MEMTRACE_H__

#include <stdlib.h>
#include "config.h"
#include "MemList.h"

#ifdef MEMORY_LEAK_CHECK

void* operator new (size_t size, const char* filename, int line);
void* operator new[] (size_t size, const char* filename, int line);

void  operator delete(void* p)throw();
void  operator delete[](void* p)throw();
#endif

#endif
