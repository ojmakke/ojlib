#include <stdlib.h>

#include "ojdarray.h"
#include "../ojllist/ojllist.h"
#include "../ojlogger/ojlogger.h"


struct OJ_IDArray
{
  struct OJ_DArray interface;
  size_t cell_size;
  size_t last_index;
  size_t num_cells;

  void* data;
  
};

/* Improved Dynamic Array. Employs linked list + regular arrays.
   This is important because it will never call on free(). We only allocate. 
   Access is not as fast as regular "dynamic" arrays which are done with memcpy
   but we can control the efficiency by increasing the "incrememnt".

   The improvement we gain from linked list is reduce access time by:
   "linked list access time "/increments.

   Basically, this a linked list of arrays of increment size!

   All memory is stored on the passed heap, so memory mangement is simple.
 */
struct OJ_IDArray* oj_idarray_make(struct HeapBlock* heap, size_t increments){return NULL;}

int oj_ida_set(struct OJ_IDArray* ida,
	       void const* value,
	       size_t var_size,
	       size_t index)
{

  LOGD("***oj_idarray_make***\n");

  if(ida == NULL)
    {
      LOGE("Null ida \n");
      return -1;
    }

  if(value == NULL)
    {
      LOGE("Null value\n");
      return -1;
    }
  if(ida->cell_size != var_size)
    {
      LOGE("Incorrect paramter type passed\n");
      return -1;
    }
  if(ida->last_index <= index)
    {
      LOGE("Array out of bounds\n");
      return -1;
    }

  
  LOGD("---oj_idarray_make---\n");
  return 0;
}

void* oj_ida_get(struct OJ_IDArray* ida, size_t index)
{

  return NULL;
}



struct OJ_DArray* oj_darray_make(struct HeapBlock* heap,
				 size_t var_size,
				 size_t increments)
{
  LOGD("***oj_darray_make***\n");
  if(heap == NULL)
    {
      LOGE("Heap is null\n");
      return NULL;
    }

  if(increments == 0)
    {
      LOGE("increment for darray cannot be 0\n");
      return NULL;
    }
  
  struct OJ_IDArray* ida = oj_heap_malloc(heap, sizeof(struct OJ_IDArray));
  if(ida == NULL)
    {
      LOGE("Error allocating ida\n");
      return NULL;
    }
  memset(ida, 0, sizeof(struct OJ_IDArray));
  ida->interface.oj_get = oj_ida_get;
  ida->interface.oj_set = oj_ida_set;
  ida->cell_size = var_size;
  ida->num_cells = increments;
  ida->last_index = (increments - 1);
  ida->data = oj_heap_malloc(heap, var_size*increments);
  if(ida->data == NULL)
    {
      LOGE("Error allocating ida->data\n");
      return NULL;
    }

  LOGD("---oj_darray_make---\n");
  return ida;
}
