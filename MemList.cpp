
#include"MemList.h"

List::List()
{
	CODE_TRACE();
	m_head = (Node*)malloc(sizeof(Node));
	m_head->_pAddr = 0;
	m_head->_filename = NULL;
	m_head->_line = 0;
	m_head->pNext = NULL;
}

List::~List()
{
	CODE_TRACE();
	PrintList();
	clear();
	free(m_head);
}

void List::Insert(const Node& node)
{
	CODE_TRACE();
	Node* p = (Node*)malloc(sizeof(Node));
	p->_pAddr = node._pAddr;
	p->_filename = node._filename;
	p->_size = node._size;
	p->_line = node._line;

	p->pNext = m_head->pNext;
	m_head->pNext = p;
}

void List::Delete(const Node& node)
{
	CODE_TRACE();
	Node *p = m_head;
	Node *q = p->pNext;
	while(q != NULL)
	{
		if(q->_pAddr == node._pAddr)
		{
			p->pNext = q->pNext;
			free(q);
		}
		p = p->pNext;
		q = q->pNext;
	}
}

void List::clear(void)
{
	CODE_TRACE();
	while(m_head->pNext != NULL)
	{
		Node *p = m_head->pNext;
		m_head->pNext = p->pNext;
		free(p);
	}
}

void List::PrintList()
{
	CODE_TRACE();
	Node *p = m_head->pNext;
	while(p != NULL)
	{
		cout << p->_filename <<" " <<p->_line <<": leak size: "<<p->_size<<endl;
		p = p->pNext;
	}
}
