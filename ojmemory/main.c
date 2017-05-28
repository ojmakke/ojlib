#include <pthread.h>
#include <stdio.h>

// This has to be after system headers to detect if pthread is included (and used)
#include "ojmemory.h"
#include "../ojlogger/ojlogger.h"

struct Params
{
  struct HeapBlock* block;
  int tid;
};

void* runtest(void* params)
{
  struct Params* mParams = params;
  
  LOGT("Thread: %d\n", mParams->tid);
  struct HeapBlock* block = mParams->block;

  int ii;
  for(ii = 0; ii < 100; ii++)
    oj_heap_malloc(block, 10);
  
  oj_heap_free(block);
  oj_heap_free(block);
  oj_heap_free(block);
  return NULL;
}


int main(int argc, char* argv[])
{

  int const max = 1000;
  pthread_t pool[max];
  int ii;

  struct HeapBlock* commonBlock, *workBlock;
  commonBlock = oj_heap_create();
  workBlock = oj_heap_create();
  struct Params* params;

  for(ii = 0; ii < max; ii++)
    {
      printf("Locking Ignore this\n");
      params = oj_heap_malloc(workBlock, sizeof(struct Params));
      params->block = commonBlock;
      params->tid = ii;
      pthread_create(&pool[ii], NULL, runtest, params);
    }

  for(ii = 0; ii < max; ii++)
    pthread_join(pool[ii], NULL);
  
  return 0;
}
