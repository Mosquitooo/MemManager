#ifndef __MEMLIST_H__
#define __MEMLIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

//#define ENABLE_TRACE

#ifdef ENABLE_TRACE
	#define CODE_TRACE()	cout << __FILE__ <<" "<<__LINE__<<endl
#else
	#define CODE_TRACE()	
#endif

typedef struct Node
{
public:
	Node(long pAddr = 0, const char* filename = NULL, int line = 0,size_t size = 0):
	_pAddr(pAddr),_filename(filename),_line(line),_size(size), pNext(NULL)
	{}
public:
	long _pAddr;
	const char* _filename;
	int _line;
	size_t _size;
	Node * pNext;
}Node;

class List
{
	
public:
	List();
	~List();
	void Insert(const Node& );
	void Delete(const Node& );
	void clear(void);
	void PrintList();
	
private:
	Node* m_head;
};

#endif
