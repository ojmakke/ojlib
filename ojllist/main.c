#include "ojllist.h"

OJLIST(int)
OJLIST(float)



int main(int argc, char* argv[])
{
  OJLListint* intList = (OJLListint *)ojllistint_create(0);
  ojllistint_push(intList, 1);
  ojllistint_push(intList, 2);
  ojllistint_push(intList, 3);
  ojllistint_push(intList, 4);
  ojllistint_push(intList, 5);
  int ii;
  OJLListint* tmpNode = intList;
  do
    {
      printf("value %d\n",tmpNode->value);
      tmpNode = tmpNode->nextNode;
      
    } while(tmpNode != NULL);
  ojllistint_free(intList);
  
}
