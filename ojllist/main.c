#include <stdio.h>
#include <pthread.h>

#include "ojllist.h"
#include "../ojmemory/ojmemory.h"

OJLIST(int,0)

struct Params
{
  OJLListint* intList;
  struct HeapBlock* heap;
  int mult;
  int tid;
};

const int maxpush = 10;
const int maxthreads = 4;
void* runtest(void* params)
{
  struct Params* mParams = params;
  printf("Thread: %d\n", mParams->tid);

  int ii;
  for(ii =mParams->mult; ii < mParams->mult+maxpush; ii++)
    {
      int* x = oj_heap_malloc(mParams->heap, sizeof(int));
      *x = ii;
      ojllistint_push(mParams->heap, mParams->intList, x);
    }
  return NULL;
}

int main(int argc, char* argv[])
{
  // To allocate all and to free later
  struct HeapBlock* myHeap;
  myHeap = oj_heap_create();
  
  pthread_t pool[maxthreads];
  // This list will be modified by multiple threads
  int x0 = 0;
  OJLListint* intList = ojllistint_create(myHeap);

  int ii;
  for(ii = 0; ii < maxthreads; ii++)
    {
      // Params to be passed to thread. 
      struct Params* mParam = oj_heap_malloc(myHeap, sizeof(struct Params));
      mParam->heap = myHeap;
      mParam->intList = intList;
      mParam->tid = ii;
      mParam->mult = ii*maxpush;
      pthread_create(&pool[ii], NULL, runtest, mParam);
    }

  for(ii = 0; ii < maxthreads; ii++)
    pthread_join(pool[ii], NULL);
  
  OJLListint* tmpNode = intList;
  __InnerListint* innerList = &intList->innerList;
  ii = 0;
  do
    {
      if(ii >= innerList->unit_full && innerList->nextNode == NULL)
	break;

      if(ii >= innerList->unit_full)
	{
	  innerList = innerList->nextNode;
	  ii = 0;
	  continue;
	}
      printf("value %d\n",innerList->value[ii++]);    
    } while(1);


  for(ii = 0; ii < intList->size; ii++)
    {
      printf("Value using API is %d\n", *ojllistint_get(intList, ii));
    }
  
  oj_heap_free(myHeap);
  return 0;
}
