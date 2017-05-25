#ifndef OJLLIST_H_
#define OJLLIST_H_
#include <stdlib.h>


#include "../ojlogger/ojlogger.h"
#include "../ojmemory/ojmemory.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct HeapBlock;

/* This macro OJLIST(type) takes in a type, such as an int or a typedef,
   and creates a linkedlist by appending OJLList+type. Then functions will be available:

   ojllist##type##_create: Returns a linked list with value of type "type".

   To free the list, you have to free the heap which was passed to the list


   ojllist##type_push: Creates a node for the linked list which has
   a member value of the value which is passed. This is added to the end of the linked list.

   The linked list has a "last" node which always points to the last node in the chain
*/


#define OJLIST(type) \
		     \
struct OJLList##type	   \
{			   \
  type value;		   \
  struct OJLList##type* nextNode; \
  struct OJLList##type* lastNode; \
};					   \
typedef struct OJLList##type OJLList##type; \
									\
 /* if *value is a ptr to stack var, it will crash */			\
OJLList##type* ojllist##type##_create(struct HeapBlock* heap, type const *value) \
{									\
  									\
  OJLList##type* newBlock = oj_heap_malloc(heap, sizeof(OJLList##type)); \
  if(newBlock == NULL)							\
    {									\
      LOGE("Cannot create llist block\n");			       	\
      return NULL;						       	\
    }									\
									\
  newBlock->lastNode = newBlock;					\
  memcpy(&newBlock->value, value, sizeof(newBlock->value));		\
  LOGD("\\\\OJULList create\n");					\
  return newBlock;							\
 }									\
									\
									\
 void ojllist##type##_push(struct HeapBlock* heap,			\
                           OJLList##type* llistBlock,			\
			   type const *value)				\
{									\
  LOGD("ojlist push**************\n");						\
  if(llistBlock == NULL)						\
    {									\
      LOGE("Passed a NULL llist\n");					\
      exit(1);								\
    }									\
  if( heap == NULL)							\
  {						\
    LOGE("Passed a NULL heap\n)");		\
    exit(1);					\
  }						\
						\
									\
  OJLList##type* lastNode = llistBlock->lastNode;			\
									\
  lastNode->nextNode = (OJLList##type*)ojllist##type##_create(heap, value); /* Local use*/ \
									\
  lastNode->nextNode->lastNode = llistBlock->lastNode;			\
									\
  llistBlock->lastNode = lastNode->nextNode;				\
  LOGD("-----------------------------\n");				\
}									\
												
#endif
