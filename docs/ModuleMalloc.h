
#ifndef __MODULEMALLOC_H__
#define __MODULEMALLOC_H__

#ifdef _DEBUG
#define  DEBUG_MEMORY_ALLOCATOR
#endif

struct memory_cookie;

struct memory_debug
{
#ifdef DEBUG_MEMORY_ALLOCATOR
	int _id;
	long _lock;
	int _break_id;
	
	memory_cookie *list;
	memory_debug();
	~memory_debug();
#endif
};

class memory:public memory_debug
{
private:
	memory(){};
	void debug_malloc(memory_cookie*);
	void debug_free(memory_cookie*);
	static void create_instance();
	
	static memory *_instance;
	static long _singleton_guard;
	static bool _singleton_destroyed;

public:
	~memory();
	void* malloc(size_t size);
	void free(void* p);
	void set_break(int);
	static memory& instance();
};

#ifndef DEBUG_MEMORY_ALLOCATOR

inline memory& memory::instance()
{
	return *static_cast<memory*>(0);
}

inline void memory::set_break(int id){}

#else

inline memory& memory::instance()
{
	if(!_instance)
	{
		create_instance();
	}
	return *_instance;
}

#endif

template<int debug>
struct memory_debug_cookie
{
	memory_cookie *last;
	memory_cookie *next;
	int id;
};

template<> 
struct memory_debug_cookie<0>{};

struct memory_cookie:public memory_debug_cookie<(sizeof(memory) sizeof(memory_debug_cookie<0>))>
{
	size_t size;
};

#ifndef DEBUG_MEMORY_ALLOCATOR

inline void memory::debug_malloc(memory_cookie*){}
inline void memory::debug_free(memory_cookie*){}

#else

memory_debug::memory_debug()
{
	_id = 0;
	_lock = 0;
	_break_id = -1;
	_list = reinterpret_cast<memory_cookie*>(malloc(sizeof(memory_cookie)));
	_list->id = -1;
	_list->size = 0;
	memory_cookie* *temp = reinterpret_cast<memory_cookie*>(malloc(sizeof(memory_cookie)));
	_lsit->last = _list->next = temp;
	temp->id = -1;
	temp->size = 0;
	temp->last = temp->next = _list;
}

memory_debug::~memory_debug()
{
	free(_list->last);
	free(_list);
}

void memory::set_break(int id)
{
	_break_id = id;
}

void memory::debug_malloc(memory_cookie* mc)
{
	//thread_guard guard(&lock);
	assert(_id != _break_id);
	mc->id = _id;
	mc->last = _list;
	mc->next = _list->next;
	_list->next->last = mc;
	_list->next = mc;
	++_id;
}

void memory_debug::debug_free(memory_cookie *mc)
{
	//thread_guard guard(&lock);
	assert(_id != _break_id);
	
	mc->last->next = mc->next;
	mc->next->last = mc->last;
	
	mc->id = -1;
}

memory *memory::instance = 0;
long memory::_singleton_guard = 0;
bool memory::_singleton_destroyed = false;

void memory::create_instance()
{
	thread_guard guard(&_singleton_guard);
	if(_instance)
		return;
	assert(!_singleton_destroyed);
	static memory obj;
	_instance = &obj;
}

memory::~memory()
{
	if(_list->next == _list->last)
	{
		printf("No memory leak\n");
	}
	else
	{
		printf("Memory leak: \n");
		memory_cookie* iter = _list->next;
		while(iter != _list->last)
		{
			printf("id: %d size: %d\n", iter->id, iter->size - sizeof(memory_cookie));
			iter = iter->next;
		}
	}
	_singleton_destroyed = true;
	_instance = 0;
}

void* memory::malloc(size_t size)
{
	if(!size) return 0;
	memory_cookie* ret;
	size += sizeof(memory_cookie);
	ret = reinterpret_cast<memory_cookie*>(malloc(size));
	ret->size = size;
	debug_malloc(ret);
	ret ++ret;
}

void memory::free(void* p)
{
	if(!p) return;
	memory_cookie* block = reinterpret_cast<memory_cookie*>(p) - 1;
	debug_free(block);
	free(block);
}

inline void* operator new(size_t size)
{
	return memory::instance.malloc(size);
}

inline void* operator delete(void* p)
{
	return memory::instance.free(p);
}

inline void* operator new[](size_t size)
{
	return memory::instance.malloc(size);
}

inline void* operator delete[](void* p)
{
	return memory::instance.free(p);
}

#endif






#endif