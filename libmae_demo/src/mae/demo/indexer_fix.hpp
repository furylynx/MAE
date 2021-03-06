//this fixes an issue with the eclipse indexer
#ifndef INDEXER_FIX_HPP_
#define INDEXER_FIX_HPP_

#ifdef USE_INDEXER_FIX

//define __SIZE_TYPE__ if not already defined
#ifndef __SIZE_TYPE__
	#define __SIZE_TYPE__ long unsigned int
#endif

typedef __SIZE_TYPE__ size_t;
typedef size_t size_type;

typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;

#if !_WIN32
typedef unsigned long int uint64_t;
#endif

#endif

#endif
