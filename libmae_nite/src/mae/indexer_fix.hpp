//this fixes an issue with the eclipse indexer
#ifndef INDEXER_FIX_HPP_
#define INDEXER_FIX_HPP_

//define __SIZE_TYPE__ if not already defined
#ifndef __SIZE_TYPE__
	#define __SIZE_TYPE__ long unsigned int
#endif

typedef __SIZE_TYPE__ size_t;
typedef size_t size_type;

typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;


#endif
