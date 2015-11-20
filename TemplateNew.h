
#ifndef __TEMPLATENEW_H__
#define __TEMPLATENEW_H__

#include <map>
#include <iostream>
using namespace std;

struct MemInfo
{
	const char* filename;
	int line;
};

class MemManager
{
public:
	typedef std::map<long, MemInfo> MemList;
public:
	void Insert(void* p, const char* pfilename, int line)
	{
		MemInfo temp = {0};
		temp.filename = pfilename;
		temp.line = line;
		m_list.insert(MemList::value_type(reinterpret_cast<long>(p), temp));
	}
	
	void Remove(void *p)
	{
		MemList::iterator it = m_list.find(reinterpret_cast<long>(p));
		if(it != m_list.end())
		{
			m_list.erase(it);
		}
		else
		{
			cout<<"free error !!!" <<endl;
		}
	}
	
	~MemManager()
	{
		MemList::iterator it = m_list.begin();
		for(; it != m_list.end(); ++it)
		{
			cout<<"filename: "<<it->second.filename;
			cout<<"line: "<<it->second.line<<endl;
		}
	}
private:
	MemList m_list;
};

static MemManager MemoryList;

template <class T>
class Alloctor
{
public:
	static void* New(int size, const char* pfilename, int line)
	{
		if(size == 0)
		{
			return NULL;
		}
		
		T *p = new T[size];
		MemoryList.Insert(p, pfilename, line);
		return p;
	}
	
	static void Delete(T* p)
	{
		MemoryList.Remove(p);
		delete [] p;
	}
};

#endif

