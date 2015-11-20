
#include "TemplateNew.h"
#include "TemplateType.h"
//#include"MemTrace.h"

#include<vector>
#include<stdio.h>

#define New(x) New(x,__FILE__,__LINE__)

class Test
{
public:
	Test(int a = 0):m_value(a)
	{
		cout<<" Destroy Test " <<endl;
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



int main()
{
	int *p = (int*)Alloctor<int>::New(10);
	//Alloctor<int>::Delete(p);
	vector<int>::iterator it = new vector<int>(10);
	
	
	Array<int, 5> a;
	a[4] = 5;
	cout << a[4] <<endl;
	
	Array<Array<int, 10>,5> b;
	b[4][9] = 6;
	cout << b[4][9] <<endl;
	
	Array<TestStruct, 5> c;
	TestStruct t = {0};
	t.b[4] = 7;
	c[4] = t;
	cout << c[4].b[4] <<endl;
	return 0;
}
