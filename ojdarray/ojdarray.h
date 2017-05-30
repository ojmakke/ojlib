#ifndef OJDARRAY_H
#define OJDARRAY_H

#include <unistd.h>

#include "../ojmemory/ojmemory.h"
#include "../ojllist/ojllist.h"

/* These attempts to make reading passing variables 
   to functions more expressive */
#define OJ_DA_TYPE(x) sizeof(x)
#define OJ_DA_VAR(x) (void* ) &x, OJ_DA_TYPE(x)



struct OJ_DArray
{
  int (* oj_set)(struct OJ_DArray* self,
		 void const* value,
		 size_t var_size,
		 size_t index);
  
  void* (*oj_get)(struct OJ_DArray* self, size_t index);
};

struct OJ_DArray* oj_darray_make(struct HeapBlock* heap,
				 size_t var_size,
				 size_t increments );

#endif
