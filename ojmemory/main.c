#include "ojmemory.h"


int main(int argc, char* argv[])
{
  struct HeapBlock* block;
  block = create_heap();
  permalloc(block, 10);
  permalloc(block, 100000);
  permalloc(block, 1000);
  free_heap(block);
  
  return 0;
}
