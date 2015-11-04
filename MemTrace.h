
#ifndef __MEMTRACE_H__
#define __MEMTRACE_H__

#include <map>
#include <stdlib.h>
#include <iostream>
#include "MemList.h"
using namespace std;

#define FILENAME_MAX_LEN 64

class MemInfo  
{
public:
	MemInfo(const char* filename, int line):_filename(filename),_line(line)
	{}
	
public:
	int _line;
	const char* _filename;
};

class MemTrace
{
public:
	MemTrace();
	~MemTrace();

public:
	List m_MemList;
};

//void* operator new (size_t size);
//void* operator new[] (size_t size);

void* operator new (size_t size, const char* filename, int line);
void* operator new[] (size_t size, const char* filename, int line);

void  operator delete(void* p);
void  operator delete[](void* p);

#endif
