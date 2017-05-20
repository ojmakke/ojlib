#include "ojhash.h"
#include "../ojlogger/ojlogger.h"
#include "../ojmemory/ojmemory.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
  struct OJLList__Cell* table;
  struct HeapBlock* myHeap;

  myHeap = create_heap();
  table = oj_hash_init(myHeap);
  LOGD("Address of table is %lu\n", table);
  LOGD("Initialized heap\n\0");
  
  char* str = "Tadfasfdsadf";
  oj_hash_add(str, NULL, table, myHeap);
 
  oj_hash_add("MyOtherString1", myHeap, table, myHeap);
  oj_hash_add("MyOtherString1", myHeap, table, myHeap);
  oj_hash_add("MyOtherString1", table, table, myHeap);
  oj_hash_add("MyOtherString", NULL, table, myHeap);

  LOGT("Result:\n");
  oj_hash_dump(table);
  
  return 0;
  
}
