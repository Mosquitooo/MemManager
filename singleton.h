

#ifndef __SINGLETON_H__
#define __SINGLETON_H__
#include <cassert>


template <typename T> 
class  CCSingleton
{
protected:
    static  T* m_Singleton;

public:
    CCSingleton( void )
    {
        assert( !m_Singleton );
        ms_Singleton = static_cast<T*>(this);
    }

    ~CCSingleton( void )
    {  
        assert( m_Singleton );  
        ms_Singleton = 0;  
    }

    static T& getSingleton( void )
    {  
        assert( m_Singleton );
        return ( *ms_Singleton );  
    }

    static T* getSingletonPtr( void )
    {  
        return ( m_Singleton );  
    }

private:

    //阻止对象赋值
    CCSingleton& operator=(const CCSingleton&) 
    { 
        return *this; 
    }

    //阻止拷贝对象
    CCSingleton(const CCSingleton&) {}
};

#endif	
