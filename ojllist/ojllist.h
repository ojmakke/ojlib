#ifndef OJLLIST_H_
#define OJLLIST_H_
#include <stdlib.h>


#include "../ojlogger/ojlogger.h"
#include "../ojmemory/ojmemory.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct HeapBlock;
#define OJMETHOD(x,  y) (x = y)

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
  OJLList##type* newBlock = (OJLList##type* )permalloc(heap, sizeof(OJLList##type)); \
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
 void ojllist##type##_push(struct HeapBlock* heap,  OJLList##type* llistBlock, type const *value) \
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
