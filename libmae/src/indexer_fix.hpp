//this fixes an issue with the eclipse indexer


//define __SIZE_TYPE__ if not already defined
#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ long unsigned int
#endif
typedef __SIZE_TYPE__ size_t;
typedef size_t size_type;
