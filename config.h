#ifndef __CONFIG_H__
#define __CONFIG_H__

#define MEMORY_LEAK_CHECK

#define FILENAME_MAX_LEN 	64

#define MAX_MEMORY_ALLOCATE (1024*1024*1024)

//#define ENABLE_TRACE

#ifdef ENABLE_TRACE
	#define CODE_TRACE()	cout << __FILE__ <<" "<<__LINE__<<endl
#else
	#define CODE_TRACE()	
#endif

#endif

