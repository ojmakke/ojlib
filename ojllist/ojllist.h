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
#define OPTIONAL_MUTEX pthread_mutex_t lock
#define OPTIONAL_MUTEX_INIT(x) pthread_mutex_init(x, NULL)
#define OPTIONAL_MUTEX_LOCK(x) pthread_mutex_lock(x)
#define OPTIONAL_MUTEX_UNLOCK(x) pthread_mutex_unlock(x)
#else
#define OPTIONAL_MUTEX
#define OPTIONAL_MUTEX_INIT(x)
#define OPTIONAL_MUTEX_LOCK(x) 
#define OPTIONAL_MUTEX_UNLOCK(x)
#endif

#define OJLEN(x) (sizeof(x)/sizeof((x)[0]))


#define OJLIST(type, _size)						\
									\
  struct __InnerList##type						\
  {									\
     type value[_size];							\
     struct __InnerList##type* nextNode;					\
     struct __InnerList##type* lastNode;					\
     size_t unit_full;							\
									\
     };									\
  typedef struct __InnerList##type __InnerList##type;			\
						\
  struct OJLList##type				\
  {						\
   __InnerList##type innerList;			\
    size_t size;				\
    OPTIONAL_MUTEX;				\
						\
  };						\
  typedef struct OJLList##type OJLList##type;				\
									\
  OJLList##type* ojllist##type##_create(struct HeapBlock* heap)		\
{									\
  LOGD("***ojllist_create***\n");					\
  									\
  OJLList##type* newBlock = oj_heap_malloc(heap, sizeof(OJLList##type)); \
  if(newBlock == NULL)							\
    {									\
      LOGE("Cannot create llist block\n");			       	\
      return NULL;						       	\
    }									\
									\
  newBlock->size = 0;							\
  newBlock->innerList.unit_full = 0;						\
  newBlock->innerList.lastNode = &newBlock->innerList ;					\
  newBlock->innerList.nextNode = NULL;				\
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
    {									\
      LOGE("Passed a NULL heap\n)");					\
      exit(1);								\
    }									\
  									\
  OPTIONAL_MUTEX_LOCK(&llistBlock->lock);				\
  __InnerList##type* lastNode = llistBlock->innerList.lastNode; \
									\
  size_t unit_size = OJLEN(lastNode->value);					\
									\
  /* No need to create new node. Local array fits */			\
  if(lastNode->unit_full < unit_size)					\
    {									\
      LOGD("Local Unit: %d value: %d\n", lastNode->unit_full, *value);		\
      memcpy(&lastNode->value[lastNode->unit_full++], value, sizeof(type));	\
    }									\
  else									\
    {									\
      LOGD("New Unit: %d value : %d\n", llistBlock->size, *value);		\
      lastNode->nextNode = oj_heap_malloc(heap, sizeof(__InnerList##type));	\
      lastNode->nextNode->unit_full = 0;				\
      lastNode->nextNode->nextNode = NULL;				\
      /* Point last node to parent's last node */			\
      lastNode->nextNode->lastNode = llistBlock->innerList.lastNode; \
									\
      llistBlock->innerList.lastNode = lastNode->nextNode;	\
      memcpy(&lastNode->nextNode->value[lastNode->nextNode->unit_full++], value, sizeof(type)); \
    }						\
									\
  llistBlock->size++;							\
  OPTIONAL_MUTEX_UNLOCK(&llistBlock->lock) ;				\
									\
  LOGD("---ojllist_push---\n");				\
}									\
									\
type* ojllist##type##_get(OJLList##type* llistBlock, size_t index)	\
{									\
    LOGD("***ojllist_get***\n"); \
    if(llistBlock == NULL) \
      { \
	LOGE("Error: llistBlock is NULL\n"); \
	return NULL; \
      } \
									\
    size_t unit_size = OJLEN(llistBlock->innerList.value);		\
    int listIndex = index/ unit_size; /* Points to the correct linked list object */ \
    int ii;								\
    __InnerList##type* innerList = &llistBlock->innerList;		\
    for(ii = 0; ii < listIndex; ii++)					\
      {									\
	if(innerList->nextNode == NULL)					\
	  {								\
	     LOGE("Error: nextNode is NULL\n");				\
          }									\
	innerList = innerList->nextNode;				\
      }									\
   return &innerList->value[index%unit_size];			\
}									\
												
#endif
