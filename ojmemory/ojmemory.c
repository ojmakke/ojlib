#include "ojmemory.h"
#include "../ojlogger/ojlogger.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>


struct HeapBlock
{
  void* allocated; /* The root node will be NULL for empty */
  struct HeapBlock* nextBlock;
  struct HeapBlock* lastBlock; 
};

struct HeapBlock* create_heap()
{
  struct HeapBlock* newBlock = (struct HeapBlock* )malloc(sizeof(struct HeapBlock));
  if(newBlock == NULL)
    {
      LOGE("Cannot create memory block\n");
      return NULL;
    }
  LOGT("Heap Block created at %lu\n", newBlock);
  memset(newBlock, 0, sizeof(struct HeapBlock));

  LOGT("Heap Block set to 0\n");
  newBlock->lastBlock = newBlock;

  LOGT("Heap last block set to self\n");
  return newBlock;
}

void add_to_heap(struct HeapBlock* heapBlock, void* blockptr)
{
  LOGT("**************\n");
  if(heapBlock == NULL)
    {
      LOGE("Passed a NULL heap block\n");
      return;
    }

  /* Imagine you pass a heap block. We want to add reference at the end */
  struct HeapBlock* lastBlock = heapBlock->lastBlock;
  LOGT("Address of lastBlock is %lu\n", lastBlock);
  
  lastBlock->nextBlock = create_heap(); /* Local use*/

  LOGT("Next Block is the now block, at %lu\n", lastBlock->nextBlock);
 
  lastBlock->nextBlock->lastBlock = heapBlock->lastBlock;
  
  /* Adjust the lastBlock pointer in the root. 
     Since this is double pointer and all previous nodes are pointing to it,
     then adjusting it will make all nodes reference the last node.
     Double pointers POWER! */
  heapBlock->lastBlock = lastBlock->nextBlock;
  LOGT("New Address of lastBlock is %lu\n", lastBlock);
  LOGT("-----------------------------\n");
}


void free_heap(struct HeapBlock* block)
{

#ifdef TESTLOG

  struct HeapBlock* testBlock = block;
  while(testBlock->nextBlock != NULL)
    {
      LOGT("Address:\t\t\t%lu\n", testBlock);
      testBlock = testBlock->nextBlock;
    }
  LOGT("Address:\t\t\t%lu\n", testBlock);
 
#endif
  
  struct HeapBlock* node;
  if(block == NULL)
    return;
  LOGT("About to free block at %lu\n", block);
  node = block->nextBlock;
  struct HeapBlock* tmpNode;
  while(node != NULL)
    {
      tmpNode = node->nextBlock;
      LOGT("Freeing address %lu\n", node);
      free(node->allocated);
      free(node);
      node = tmpNode;
      LOGT("Next Node to free is %lu\n", node);
    }
  LOGT("OJ lastBlock Free\n");
}


void* permalloc(struct HeapBlock* block, size_t size)
{
  void* mem = malloc(size);
  if(mem == NULL)
    {
      LOGE("permalloc\n");
      return NULL;
    }
	      
  add_to_heap(block, mem);
  return mem;
}
