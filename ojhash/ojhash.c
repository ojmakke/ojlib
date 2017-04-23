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
  void** ptr; /* Pointer to pointer to actual object */
  size_t size;
};
OJLIST(__Cell)

OJLList__Cell* oj_init_hash(struct HeapBlock* heap)
{
  OJLList__Cell* table = (OJLList__Cell*) permalloc(heap, sizeof(OJLList__Cell));
  table->lastNode = NULL;
  table->nextNode = NULL;
  table->value.ptr = NULL;
  table->value.hash = 0;
  table->value.size = 0;
  return table;
}

void oj_add_to_hash(char* str,
		    void* object,
		    struct OJLList__Cell* llist,
		    struct HeapBlock* heap)
{
  unsigned long hash = 5381;
  int c;

  while((c = *str++))
    {
      hash = ((hash << 5) + hash) + c;
    }

  OJLList__Cell* tmpItem = llist;
  
  while(tmpItem != NULL)
    {
      if(tmpItem->value.ptr == NULL ) /* Indication of end of list */
	{
	  break;
	}
      if(tmpItem->value.hash == hash)
	{
	  break;
	}
      tmpItem = llist->nextNode;
    };

  OJLList__Cell* node;
  if(tmpItem->value.ptr == NULL) /* End of List */
    {
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
  OJLList__Cell** prev;
  OJLList__Cell** next;
  OJLList__Cell** tmpNode;

  OJLList__Cell** beginNode;
  
  beginNode = llist; /* This won't change if we change *llist */
  tmpNode = llist;
  prev = llist;
  next = llist;
  
  if(tmpNode == NULL || *tmpNode == NULL)
    {
      LOGE("Error, passed NULL linked list\n");
      return;
    }
  if((*tmpNode)->lastNode == NULL && (*tmpNode)->nextNode == NULL)
    {
      return; /* Only 1 item */
    }

  *prev = *tmpNode; /* Initial condition is same, then prev is previous node */
  while(1)
    {
      /* This implies node is at end. It has no next node */
      if((*tmpNode)->nextNode == NULL)
	{
	  if(done)
	    {
	      return; /* This is how this loop ends */
	    }
	  *tmpNode = *llist; /* Reset to beginning */
	  *prev = *tmpNode;
	  done = 1;
	  continue;
	}
      /* Note the >, not >=. prev = tmpNode won't execute */
      /* This condition applies to all nodes which have next node */
      /* And prev node is still pointing to the previous node */
      if((*tmpNode)->value.hash > (*tmpNode)->nextNode->value.hash)
	{
	  *next = (*tmpNode)->nextNode; /* To be the "this" node */

	  /* Replace the beginNode to have a "meaningful" chain */
	  if(*tmpNode == beginNode)
	    {
	      
	    }
	  *tmpNode = (*tmpNode)->nextNode; /* To be the next, "this->next" node */

	  (*prev)->nextNode = *next; /* This was pointing to tmpNode */
	  done = 0; /* We changed something */
	}

      /* Note that *tmpNode is pointing ot next node. It will keep moving */
    }
}


