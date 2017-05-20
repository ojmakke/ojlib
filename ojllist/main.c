#include "ojllist.h"
#include "../ojmemory/ojmemory.h"

OJLIST(int)
OJLIST(float)



int main(int argc, char* argv[])
{
  struct HeapBlock* myHeap;
  myHeap = create_heap();
  int x0 = 0;
  
  OJLListint* intList = (OJLListint *)ojllistint_create(myHeap, &x0);
  int x1, x2, x3, x4, x5;
  x1 = 1;
  x2 = 2;
  x3 = 3;
  x4 = 4;
  x5 = 5;
  ojllistint_push(myHeap, intList, &x1);
  ojllistint_push(myHeap, intList, &x2);
  ojllistint_push(myHeap, intList, &x3);
  ojllistint_push(myHeap, intList, &x4);
  ojllistint_push(myHeap, intList, &x5);
  
  OJLListint* tmpNode = intList;
  do
    {
      printf("value %d\n",tmpNode->value);
      tmpNode = tmpNode->nextNode;
      
    } while(tmpNode != NULL);
  free_heap(myHeap);
  return 0;
  
}
