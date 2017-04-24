#include "ojhash.h"
#include "../ojlogger/ojlogger.h"
#include "../ojmemory/ojmemory.h"
#include "../ojllist/ojllist.h"


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* to hold memory location */
typedef void* voidptr;
OJLIST(voidptr);

struct __Cell
{
  unsigned long hash;
  OJLListvoidptr* objects; /* Linked List to hold address of objects */
};

typedef struct __Cell __Cell;

OJLIST(__Cell)

struct OJLList__Cell* oj_hash_init(struct HeapBlock** heap)
{
  LOGD("oj_hash_init\n");
  struct __Cell myCell;
  memset(&myCell, 0, sizeof(__Cell));
  myCell.hash = 0;
  
  OJLList__Cell* table = ojllist__Cell_create(&myCell);
  table->nextNode = NULL;
  table->value.objects = NULL;
  //table->value.objects->nextNode = NULL;

  table->value.hash = 0;
  return table;
}

void oj_hash_add(char* str,
		 void* object,
		 struct OJLList__Cell* llist,
		 struct HeapBlock* heap)
{
  LOGD("oj_hash_add\n");
  /* Calculate the hash */
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
  LOGD("Hash is %lu\n", hash);

  /* Find if hash already exist */
  OJLList__Cell* tmpItem = llist;
  while(tmpItem != NULL)
    {
      if(tmpItem->value.hash == hash)
	{
	  break;
	}
      tmpItem = tmpItem->nextNode;
    };

  /* Get the node for the hash. If new, allocate */
  __Cell* cellNode = &llist->value;

  OJLListvoidptr* newMem; 
  if(tmpItem == NULL) /* End of List */
    {
      LOGD("Allocating node\n");
      cellNode->hash = hash;
      newMem = ojllistvoidptr_create(&object);
      LOGD("(((((newMem is at %lu %lu)))))\n", newMem, *newMem);
      cellNode->objects = newMem;
      //   ojllist__Cell_push(llist, &node);
      
      LOGD("We have: llist at %lu, llist node is %lu and node's llist is %lu\n",
	   llist, llist->value.objects, llist->value.objects->lastNode);
    }

  else
    {
      LOGD("\n\n\nHash exists:  %lu!\n", tmpItem->value);
      cellNode = &tmpItem->value;
      newMem = cellNode->objects;
      
      LOGD("Addr is %lu\n", *newMem);
      ojllistvoidptr_push(newMem, &object);
      printf("Dumping:\n");

      OJLListvoidptr* mobj = cellNode->objects;
      while(mobj->value != NULL)
	{
	  printf("%lu\n", mobj->value);
	  if(mobj->nextNode == NULL) break;
	  mobj = mobj->nextNode;
	  LOGD("Next\n");
	}
    }

  /* Now we are pointing to the node with the correct hash.
     Insert new object reference in its linked list */
  
  //ojllistvoidptr_push(&node.objects, &object);
  LOGD("Next Node address is %lu\n", llist->nextNode);
  LOGD("////oj_hash_add\n");
 
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

void oj_hash_dump(struct OJLList__Cell* llist)
{
  OJLList__Cell* tmpList = llist;
  while(tmpList != NULL)
    {
      LOGD("hash: %lu\n",  tmpList->value.hash);
      LOGD("Hash objects are at %lu\n",  tmpList->value.objects);
    
      OJLListvoidptr* tmpObj = tmpList->value.objects;
      int ii = 0;
      while(1)
	{
	  ii++;
	  LOGI("\t %d: address: %lu\n", ii, tmpObj->value);

	  if(tmpObj->nextNode == NULL)
	    break;
	  tmpObj = tmpObj->nextNode;
	} 
      tmpList = tmpList->nextNode;
    }
}


