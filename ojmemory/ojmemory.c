#include "ojmemory.h"
#include "../ojlogger/ojlogger.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// If something outside has included this
#ifdef OJ_POSIX_THREAD
#include <pthread.h>
#endif



struct HeapBlock
{
  void* allocated; /* The root node will be NULL for empty */
  struct HeapBlock* nextBlock;
  struct HeapBlock* lastBlock;
#ifdef OJ_POSIX_THREAD
  pthread_mutex_t lock;
#endif
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
#ifdef OJ_POSIX_THREAD
  pthread_mutex_init(&newBlock->lock, NULL);
#endif
  
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

  /* Imagine you pass a heap block. We want to add reference at the end 
     For multithreaded, this is tricky because lastBlock can actually change.
     So we have to lock mutex
   */
#ifdef OJ_POSIX_THREAD
  LOGD("\t\t\tLocking mutex in add\n");
  pthread_mutex_lock(&heapBlock->lock);
  LOGD("\t\t\tLocking SUCCEEDED in add\n");
#endif
  struct HeapBlock* lastBlock = heapBlock->lastBlock;
  lastBlock->nextBlock = oj_heap_create(); /* Local use*/
  lastBlock->nextBlock->lastBlock = heapBlock->lastBlock;
  
  heapBlock->lastBlock = lastBlock->nextBlock;
  LOGD("New Address of lastBlock is %lu\n", lastBlock);
#ifdef OJ_POSIX_THREAD
  LOGD("\t\t\tUnlocking mutex in add\n");
  pthread_mutex_unlock(&heapBlock->lock);
#endif
  LOGD("--oj_heap_add--\n");
}

void oj_heap_free(struct HeapBlock* block)
{

  LOGD("**oj_heap_free**\n");
  
  struct HeapBlock* node;
  if(block == NULL)
    {
      LOGE("Passed block is NULL\n");
      return;
    }
  
  LOGD("About to free block at %lu\n", block);
  // We have to lock. Imagine freeing and then something adds to us. Bad!
  // Notice that we do not clear the "main" node, which is supposed
  // to stay empty, by design. This is so that, after free, if something
  // adds memory to heap block, no crash will happen.
  // It is also possible to call this function on same object multiple times
  // Notice that we only operate on the mutex of the root node

#ifdef OJ_POSIX_THREAD
  LOGD("\t\t\t\t\t\tLocking mutex in free\n");
  pthread_mutex_lock(&block->lock);
  LOGD("\t\t\t\t\t\tLocking SUCCEEDED in free\n");
#endif
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

  block->nextBlock = NULL;
  block->lastBlock = block;
  block->allocated = NULL;

#ifdef OJ_POSIX_THREAD
  LOGD("\t\t\t\t\t\tUnlocking mutex in free\n");
  pthread_mutex_unlock(&block->lock);
#endif
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
