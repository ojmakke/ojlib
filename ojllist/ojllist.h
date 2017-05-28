#ifndef OJLLIST_H_
#define OJLLIST_H_
#include <stdlib.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifdef OJ_POSIX_THREAD
#include <pthread.h>
#endif

#include "../ojlogger/ojlogger.h"
#include "../ojmemory/ojmemory.h"

struct HeapBlock;

/* This macro OJLIST(type) takes in a type, such as an int or a typedef,
   and creates a linkedlist by appending OJLList+type. Then functions will be available:

   ojllist##type##_create: Returns a linked list with value of type "type".

   To free the list, you have to free the heap which was passed to the list


   ojllist##type_push: Creates a node for the linked list which has
   a member value of the value which is passed. This is added to the end of the linked list.

   The linked list has a "last" node which always points to the last node in the chain
*/

#ifdef OJ_POSIX_THREAD
#define OPTIONAL_MUTEX pthread_mutex_t lock;
#define OPTIONAL_MUTEX_INIT(x) pthread_mutex_init(x, NULL);
#define OPTIONAL_MUTEX_LOCK(x) pthread_mutex_lock(x);
#define OPTIONAL_MUTEX_UNLOCK(x) pthread_mutex_unlock(x);
#else
#define OPTIONAL_MUTEX
#define OPTIONAL_MUTEX_INIT(x)
#define OPTIONAL_MUTEX_LOCK(x) 
#define OPTIONAL_MUTEX_UNLOCK(x)
#endif


#define OJLIST(type) \
		     \
struct OJLList##type	   \
{			   \
  type value;		   \
  struct OJLList##type* nextNode; \
  struct OJLList##type* lastNode; \
  OPTIONAL_MUTEX			   \
					   \
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
  OPTIONAL_MUTEX_LOCK(&llistBlock->lock)					\
  OJLList##type* lastNode = llistBlock->lastNode;			\
									\
  lastNode->nextNode = (OJLList##type*)ojllist##type##_create(heap, value); /* Local use*/ \
									\
  lastNode->nextNode->lastNode = llistBlock->lastNode;			\
									\
  llistBlock->lastNode = lastNode->nextNode;				\
  OPTIONAL_MUTEX_UNLOCK(&llistBlock->lock) ;				\
  LOGD("-----------------------------\n");				\
}									\
												
#endif
