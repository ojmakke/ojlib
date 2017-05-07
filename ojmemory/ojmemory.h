#ifndef OJMEM_H_
#define OJMEM_H_

#include <stdlib.h>

/* This is used when we need to allocate memory "indefinitly" until program exists
   We use this to remember what we want to free.
   If you free blocks somewhere else, crash will happen
   Do not use this if you want to free allocations before program ends

*/

struct HeapBlock;

struct HeapBlock* create_heap();
void add_to_heap(struct HeapBlock* heapBlock, void* blockPtr);
void free_heap(struct HeapBlock* block);

void* permalloc(struct HeapBlock* block, size_t size);

#endif
