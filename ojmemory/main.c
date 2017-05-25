#include "ojmemory.h"


int main(int argc, char* argv[])
{
  struct HeapBlock* block;
  block = oj_heap_create();
  oj_heap_malloc(block, 10);
  oj_heap_malloc(block, 100000);
  oj_heap_malloc(block, 1000);
  oj_heap_free(block);
  
  return 0;
}
