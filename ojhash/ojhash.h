#ifndef OJHASH_H_
#define OJHASH_H_

#include "../ojmemory/ojmemory.h"

struct OJLList__Cell;

/* All memory for the list is allocated on a given heap */
/* Heap is assumed to be initialized outside and passed */
/* Therefore, it must be cleared outside */
struct OJLList__Cell* oj_hash_init(struct HeapBlock** heap);

void oj_hash_add(char* str, 
		 void* object, 
		 struct OJLList__Cell* llist, 
		 struct HeapBlock* heap);

/* The reason for the sort is that the root address itself may be sorted */
void oj_hash_sort(struct OJLList__Cell** llist);

void oj_hash_dump(struct OJLList__Cell* llist);

#endif
