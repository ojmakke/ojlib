#ifndef OJHASH_H_
#define OJHASH_H_

#include "../ojmemory/ojmemory.h"

/* Impelemntation of hash table 

 */

struct OJLList__Cell;

/* All memory for the list is allocated on a given heap */
/* Heap is assumed to be initialized outside and passed here */
/* Therefore, all memory associated with this hash table can be freed
   by freeing the heap */

/* Create a hash table (for strings) and store in heap */
struct OJLList__Cell* oj_hash_init(struct HeapBlock* heap);

/* Add to hash table llist, using heap memory block, 
   the hash of str related to object.
   The object reference will be stored in hash for easy access */
void oj_hash_add(const char* str, 
		 const void* const  object, 
		 struct OJLList__Cell* llist, 
		 struct HeapBlock* heap);

/* The reason for the sort is that the root address itself may be sorted */
void oj_hash_sort(struct OJLList__Cell** llist);

/* Display what is in the hash */
void oj_hash_dump(const struct OJLList__Cell* llist);

#endif
