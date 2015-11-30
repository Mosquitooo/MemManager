
//#include "TemplateNew.h"
#include "TemplateType.h"
#include "MemTrace.h"

#include<vector>
#include<map>
#include<stdio.h>
#include"config.h"

//#define New(x) New(x,__FILE__,__LINE__)

#ifdef MEMORY_LEAK_CHECK
	#define new new(__FILE__, __LINE__)
#endif

class Test
{
public:
	Test(int a = 0):m_value(a)
	{
		cout<<" Create Test " <<endl;
	}
	~Test()
	{
		cout<<" Destroy Test " <<endl;
	}
public:
	int m_value;
};

struct TestStruct
{
	int a;
	Array<int, 10> b;
	Array<char,10> str;
};

void MemoryLeakTest()
{
	Test* pnew = new Test(10);
	int* pint = new int[10];
	delete pnew;
	//delete [] pint;
	map<int, int> map_a;
	map_a.insert(map<int, int>::value_type(1,1));
}

void ArrayBeyondTest()
{
	Array<int, 5> a;
	a[4] = 5;
	cout << a[4] <<endl;
	
	//无法检测内存越界
	int* p1 = a.GetPtr();
	p1[5] = 6;
	cout << p1[5] <<endl;
	
	//无法使用p[i]
	Array<int, 5> *p2 = a.getptr();

	
	Array<Array<int, 10>,5> b;
	b[4][9] = 6;
	cout << b[4][9] <<endl;
	
	Array<TestStruct, 5> c;
	TestStruct t = {0};
	t.b[4] = 7;
	c[4] = t;
	cout << c[4].b[4] <<endl;
}


int main()
{
	//int *p = (int*)Alloctor<int>::New(10);
	//Alloctor<int>::Delete(p);
	MemoryLeakTest();
	ArrayBeyondTest();
	
	return 0;
}
