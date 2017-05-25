#ifndef OJMEM_H_
#define OJMEM_H_

#include <stdlib.h>

/* This is used when we need to allocate related memory in 
   several parts of the program until certain condition are met, 
   then we want to free that group of memory allocations. 
   We use this to remember what we want to free.
   If you free blocks somewhere else, crash will happen, 
   so make sure that if you use oj_heap_malloc(), you use oj_heap_free()

*/

struct HeapBlock;

/* Create a pointer to allocated heap. 
   To free this heap allocation and all memory it is holding, 
   call oj_heap_free(). Do not use free() or same memory will be free()ed twice
*/
struct HeapBlock* oj_heap_create();

/* Add anything allocated with "malloc()" of stdlib to the heap. 
   Freeing the heap will call free() on blockPtr */
void oj_heap_add(struct HeapBlock* heapBlock, void* blockPtr);


/* Free all the memory held in the heap, including the heap pointer */
void oj_heap_free(struct HeapBlock* block);

/* This replaces malloc(). It calls on oj_heap_create() and oj_heap_add()
   to allocate size_t of memory and store it in the heap block */
void* oj_heap_malloc(struct HeapBlock* block, size_t size);

#endif
