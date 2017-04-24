#ifndef OJLLIST_H_
#define OJLLIST_H_
#include <stdlib.h>


#include "../ojlogger/ojlogger.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define OJMETHOD(x,  y) (x = y)

#define OJLIST(type) \
		     \
struct OJLList##type \
{			   \
  type value;		   \
  struct OJLList##type* nextNode; \
  struct OJLList##type* lastNode; \
};					   \
typedef struct OJLList##type OJLList##type; \
					   \
OJLList##type* ojllist##type##_create(type *value)			\
 {									\
  OJLList##type* newBlock = (OJLList##type* )malloc(sizeof(OJLList##type)); \
  if(newBlock == NULL)							\
    {									\
      LOGE("Cannot create llist block\n");					\
      return NULL;								\
    }									\
  LOGT("LList Block created at %lu\n", newBlock);			\
  memset(newBlock, 0, sizeof(struct OJLList##type));			\
									\
  LOGT("Heap Block set to 0\n");					\
  newBlock->lastNode = newBlock;					\
  newBlock->value = *value;						\
  LOGT("Heap last block set to self\n");				\
  return newBlock;							\
 }									\
									\
									\
 void ojllist##type##_push(OJLList##type* llistBlock, type *value)	\
{									\
  LOGT("ojlist push**************\n");						\
  if(llistBlock == NULL)						\
    {									\
      LOGE("Passed a NULL llist\n");					\
      return;								\
    }									\
																	\
  OJLList##type* lastNode = llistBlock->lastNode;			\
  LOGT("Address of lastNode is %lu\n", lastNode);			\
									\
  lastNode->nextNode = (OJLList##type*)ojllist##type##_create(value); /* Local use*/ \
  LOGT("Value of nextNode is %lu\n", (type) lastNode->value);		\
  LOGT("Next Block is the now block, at %lu\n", lastNode->nextNode);	\
									\
  lastNode->nextNode->lastNode = llistBlock->lastNode;			\
									\
  llistBlock->lastNode = lastNode->nextNode;				\
  LOGT("New Address of lastNode is %lu\n", llistBlock->lastNode);			\
  LOGT("-----------------------------\n");				\
}									\
									\
									\
void ojllist##type##_free(OJLList##type* block)				\
{								\
								\
  OJLList##type* node;						\
  if(block == NULL)						\
    return;							\
  LOGT("About to free block at %lu\n", block);			\
  node = block->nextNode;					\
  OJLList##type* tmpNode;					\
  while(node != NULL)						\
    {								\
      tmpNode = node->nextNode;				\
      LOGT("Freeing address %lu\n", node);			\
      free(node);						\
      node = tmpNode;						\
      LOGT("Next Node to free is %lu\n", node);			\
    }								\
  LOGT("OJ lastNode Free\n");					\
}								\
						
#endif
