#include "ojstack.h"

#include <stdio.h>


#define MSG(x) printf("%s\n", x)
#define PASSED printf("Passed\n");
#define FAILED printf("Failed\n");

void fill(ErrorStack** stack1, ErrorStack** stack2)
{

  stackPush(stack1, "Error1 stack1", ERROR);
  // MSG(stack1->message);
  stackPush(stack1, "Warning1 stack1", WARNING);
  //MSG(stack1->lower->message);
  stackPush(stack1, "Message1 stack1", SUCCESS);
  stackPush(stack1, "Error2 stack1", ERROR);

  
  stackPush(stack2, "Error1 stack2", ERROR);
  stackPush(stack2, "Warning1 stack2", WARNING);
  stackPush(stack2, "Message1 stack2", SUCCESS);
  stackPush(stack2, "Error2 stack2", ERROR);

}

int main(int argc, char* argv[])
{
  MSG("Test Started");
  MSG("Creating 2 stacks");

  ErrorStack *stack1p, *stack2p;
  ErrorStack stack1, stack2;
  stack1 = makeNewStack();
  stack2 = makeNewStack();
  stack1p = &stack1;
  stack2p = &stack2;

  MSG("Adding 2 errors, 1 Warning, 1 Message to both stacks");
  fill(&stack1p, &stack2p);
  // MSG(stack1.lower->message);

  MSG("Dumping all stack1");

  stackDumpV(&stack1p);

  MSG("Dumping with error all stack2");
  stackDumpE(&stack2p);

  fill(&stack1p, &stack2p);
  MSG("Silently dumping stack1 and 2");
  stackRemove(&stack1p);
  stackRemove(&stack2p);
  MSG("END");

  return 0;
  
}
