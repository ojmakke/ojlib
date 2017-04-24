#include "ojhash.h"
#include "../ojlogger/ojlogger.h"
#include "../ojmemory/ojmemory.h"
#include "../ojllist/ojllist.h"


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct __Cell
{
  unsigned long hash;
  void** ptr; /* Pointer to pointer to actual object for which this hash is for */
  size_t size;
};

typedef struct __Cell __Cell;

OJLIST(__Cell)

struct OJLList__Cell* oj_hash_init(struct HeapBlock** heap)
{
  LOGD("oj_hash_init\n");
  OJLList__Cell* table = (OJLList__Cell*) permalloc(*heap, sizeof(OJLList__Cell));
  table->lastNode = NULL;
  table->nextNode = NULL;
  table->value.ptr = NULL;
  table->value.hash = 0;
  table->value.size = 0;
  LOGD("\\\oj_hash_init\n");
  return table;
}

void oj_hash_add(char* str,
		 void* object,
		 struct OJLList__Cell* llist,
		 struct HeapBlock* heap)
{
  unsigned long hash = 5381;
  int c;

  if(heap == NULL)
    {
      LOGE("Error: Passed null heap to oj_hash_add\n");
      exit(1);
    }

  if(llist == NULL)
    {
      LOGE("Error: Passed null llist to oj_hash_add\n ");
      exit(1);
    }
  
  while((c = *str++))
    {
      hash = ((hash << 5) + hash) + c;
    }
  OJLList__Cell* tmpItem = llist;
  LOGD("Hash is %d\n", hash);

  while(tmpItem != NULL)
    {
      if(tmpItem->value.ptr == NULL ) /* Indication of end of list */
	{
	  break;
	}
      ;
      if(tmpItem->value.hash == hash)
	{
	  break;
	}
      tmpItem = llist->nextNode;
    };

  OJLList__Cell* node;
  if(tmpItem->value.ptr == NULL) /* End of List */
    {
      LOGD("Allocating node\n");
      node = (OJLList__Cell*) permalloc(heap, sizeof(OJLList__Cell));
      node->value.hash = hash;
    }
  else
    {
      node = tmpItem;
    }

  /* Node is either new, or one which we found at tmpItem */
  node->value.ptr[node->value.size] = permalloc(heap, sizeof(void*));
  node->value.ptr[node->value.size] = object;
  node->value.size++;
  
}

void oj_hash_sort(struct OJLList__Cell** llist)
{
  int done = 0;
  OJLList__Cell* prev;
  OJLList__Cell* next;
  OJLList__Cell* tmpNext;
  OJLList__Cell* tmpNode;

  if(llist == NULL)
    {
      LOGE("Error, Passed NULL linked list\n");
    }
  tmpNode = *llist; /* Start by making temp use same root. After sort, root changes */
  prev = NULL; /* Root has no prev */
  next = *llist;
  
  if(tmpNode == NULL)
    {
      LOGE("Error, passed NULL linked list\n");
      return;
    }
  if((tmpNode)->lastNode == NULL && (tmpNode)->nextNode == NULL)
    {
      return; /* Only 1 item */
    }

  while(1)
    {
      /* This implies node is at end. It has no next node */
      if((tmpNode)->nextNode == NULL)
	{
	  if(done)
	    {
	      return; /* This is how this loop ends */
	    }
	  tmpNode = *llist; /* Reset to beginning */
	  prev = NULL;
	  done = 1;
	  continue;
	}
      /* Note the >, not >=. prev = tmpNode won't execute */
      /* This condition applies to all nodes which have next node */
      /* And prev node is still pointing to the previous node */
      if((tmpNode)->value.hash > (tmpNode)->nextNode->value.hash)
	{
	  next = tmpNode->nextNode;
	  tmpNext = next->nextNode; /* Memorize the address which will be next*/
	  next->nextNode = tmpNode; /* This puts next before tmpNode */
	  tmpNode->nextNode = tmpNext; /* This was next's next. */

	  /* Now we need to update prev. If prev is null --> this was root */
	  /* If this was root, update the main root */
	  if(prev == NULL)
	    {
	      *llist = next;
	    }

	  prev = next;
	  done = 0; /* We changed something */
	}

      /* Note that *tmpNode is pointing ot next node. It will keep moving */
    }
}


