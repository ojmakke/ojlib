#include "ojhash.h"
#include "../ojlogger/ojlogger.h"
#include "../ojmemory/ojmemory.h"
#include "../ojllist/ojllist.h"


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* to hold memory location */
typedef const void* voidptr;
OJLIST(voidptr, 100);

struct __Cell
{
  unsigned long hash;
  OJLListvoidptr* objects; /* Linked List to hold address of objects. 
			      It is a pointer because we want to set it 
			      directly from create_heap() */
};

/* To be able to call the macro with same label as the struct tag */
typedef struct __Cell __Cell;

OJLIST(__Cell,100)

struct OJLList__Cell* oj_hash_init(struct HeapBlock* heap)
{
  LOGD("**oj_hash_init**\n");
  struct __Cell myCell;
  memset(&myCell, 0, sizeof(__Cell));
  myCell.hash = 0;

  OJLList__Cell* table = ojllist__Cell_create(heap, &myCell);
  table->nextNode = NULL;
  table->value.objects = NULL;
  //table->value.objects->nextNode = NULL;

  table->value.hash = 0;
  LOGD("--oj_hash_init--\n");
  return table;
}

void oj_hash_add(const char* str,
		 const void* const object,
		 struct OJLList__Cell* llist,
		 struct HeapBlock* heap)
{
  LOGD("**oj_hash_add**\n");
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
  OJLList__Cell* tmpCellList = llist;
  while(tmpCellList != NULL)
    {
      if(tmpCellList->value.hash == hash)
	{
	  break;
	}
      tmpCellList = tmpCellList->nextNode;
    };

  /* Get the node for the hash. If new, allocate */
  __Cell cellNode;
  memset(&cellNode, 0, sizeof(cellNode));

  OJLListvoidptr* newMem; 
  if(tmpCellList == NULL) /* End of List */
    {
      cellNode.hash = hash;
      newMem = ojllistvoidptr_create(heap, &object);
      newMem->nextNode = NULL;
      cellNode.objects = newMem;
      ojllist__Cell_push(heap, llist, &cellNode);
      tmpCellList = llist->lastNode; 
    }

  else
    {
      newMem = tmpCellList->value.objects;
      ojllistvoidptr_push(heap, newMem, &object);

      OJLListvoidptr* mobj = tmpCellList->value.objects;
      while(mobj->value != NULL)
	{
	  if(mobj->nextNode == NULL) break;
	  mobj = mobj->nextNode;
	}
    }

  LOGD("--oj_hash_add--\n");
 
}

void oj_hash_sort(struct OJLList__Cell** llist)
{
  LOGD("**oj_hash_sort**\n");
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
  LOGD("--oj_hash_sort--\n");
}

void oj_hash_dump(const struct OJLList__Cell* llist)
{
  LOGD("**oj_hash_dump**\n");
  const OJLList__Cell* tmpList = llist;
  while(tmpList != NULL)
    {
      LOGD("hash: %lu\n",  tmpList->value.hash);
      LOGD("Hash objects are at %lu\n",  tmpList->value.objects);
    
      OJLListvoidptr* tmpObj = tmpList->value.objects;
      printf("Head, Last, Value %lu \n", tmpList->value.objects);
      if(tmpObj == NULL)
	{
	  LOGD("Cell Chain empty! Something went wrong\n");
	  tmpList = tmpList->nextNode;
	  continue;
	}
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
  LOGD("--oj_hash_dump--\n");
}


