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

struct HeapBlock* oj_heap_create()
{
  LOGD("**oj_heap_create()**\n");
  struct HeapBlock* newBlock = malloc(sizeof(struct HeapBlock));
  if(newBlock == NULL)
    {
      LOGE("Cannot create memory block\n");
      return NULL;
    }
  LOGD("Heap Block created at %lu\n", newBlock);
  memset(newBlock, 0, sizeof(struct HeapBlock));
  newBlock->lastBlock = newBlock;
  LOGD("--oj_heap_create()--\n");
  return newBlock;
}

void oj_heap_add(struct HeapBlock* heapBlock, void* blockptr)
{
  LOGD("**oj_heap_add**\n");
  if(heapBlock == NULL)
    {
      LOGE("Passed a NULL heap block\n");
      return;
    }

  /* Imagine you pass a heap block. We want to add reference at the end */
  struct HeapBlock* lastBlock = heapBlock->lastBlock;
  lastBlock->nextBlock = oj_heap_create(); /* Local use*/
  lastBlock->nextBlock->lastBlock = heapBlock->lastBlock;
  
  heapBlock->lastBlock = lastBlock->nextBlock;
  LOGD("New Address of lastBlock is %lu\n", lastBlock);
  LOGD("--oj_heap_add--\n");
}

void oj_heap_free(struct HeapBlock* block)
{

  LOGD("**oj_hea_free**\n");
  
  struct HeapBlock* node;
  if(block == NULL)
    {
      LOGE("Passed block is NULL\n");
      return;
    }
  
  LOGD("About to free block at %lu\n", block);
  node = block->nextBlock;
  struct HeapBlock* tmpNode;
  while(node != NULL)
    {
      tmpNode = node->nextBlock;
      LOGD("Freeing address %lu\n", node);
      free(node->allocated);
      free(node);
      node = tmpNode;
      LOGD("Next Node to free is %lu\n", node);
    }
  LOGD("--oj_heap_free--\n");
}


void* oj_heap_malloc(struct HeapBlock* block, size_t size)
{
  LOGD("**oj_heap_malloc**\n");
  void* mem = malloc(size);
  if(mem == NULL)
    {
      LOGE("malloc failed in oj_heap_malloc\n");
      return NULL;
    }
	      
  oj_heap_add(block, mem);
  LOGD("--oj_heap_malloc--\n");
  return mem;
}
