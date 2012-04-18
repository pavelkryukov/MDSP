/*
 * cache.h
 *
 *  Created on: Apr 12, 2012
 *      Author: Artemy Margaritov
 */

#ifndef CACHE_H_
#define CACHE_H_

#include <vector>

using namespace std;
enum { full = 0}; 				// define for full-associative cache
typedef unsigned int uint;

struct Block;
struct Set;

/** Return miss rate for cache with entered characteristics and data from filename 'name'.*/
double calcMissRate ( uint size, uint ways, uint block_size, uint addr_len, char* name);


/**
 * This class is emulator of processor's cache.
 * It supports following settings:
 * 		size 	   		 	   - is a number of data bytes that can be stored in the cache,
 * 		ways 	   		 	   - is a number of associative ways in a set,
 * 								 for creating full-associative cache you can use define 'full'.
 * 		block_size 		 	   - is a number of Bytes in a data block,
 * 		addr_size_in_bit 	   - is a number of bits in address.
 */
class Cache
{
	uint ways_; 				//number of ways can be not a power of two
	uint block_size_in_bit_;
	uint sets_; 				//number of sets can be only a power of two
	uint set_addr_in_bit_;
	uint tag_in_bit_;

	uint miss_number_;
	uint request_number_;

	uint mask_index_;
	uint mask_tag_;

	/** return index of cache for target address.*/
	uint getIndex( uint addr);

	/** return tag of target address.*/
	uint getTag	 ( uint addr);

	/** Politics of replacement.
	 *  If there are no free blocks in the set
	 *  this algorithm will be used to calculate number of block in the set
	 *  which will be replace.
	 */
	void replace( Set* set, uint tag);

	vector<Set> cache_;

public:
    Cache( unsigned int size, unsigned int ways,
           unsigned int block_size,
           unsigned int addr_size_in_bit);

    /** Gets address and checks availability data for him in cache,
     *  if address was not found, it would be added to cache.
     */
    void processRead( unsigned int addr);
    /** Returns miss rate.*/
    double getMissRate() const;
};

/**
 * This structure emulates line of block,
 * which consist of different ways, named "set".
 */
struct Set
{
		Set( uint ways);
		vector<Block> blocks_;
		uint replaceable_;
};

/**
 * This structure emulates data block.
 */
struct Block
{
	Block();
	uint tag_;
	bool valid_;
};

#endif /* CACHE_H_ */
