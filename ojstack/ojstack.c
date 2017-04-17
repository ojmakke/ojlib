#include "ojstack.h"
#include "../ojlogger/ojlogger.h"

#include <stdlib.h>
#include <stdio.h>

ErrorStack makeNewStack()
{
  ErrorStack stack;
  stack.message = "Top";
  stack.value = SUCCESS;
  stack.lower = NULL;
  return stack;
}

ErrorStack* stackPush(ErrorStack** theStack, char* message, StackEnums value)
{
  if(theStack == NULL || *theStack == NULL) return NULL;
  ErrorStack* newLayer = (ErrorStack* ) malloc(sizeof(ErrorStack));
  if(newLayer == NULL)
    {
      LOGE("Cannot allocate layer to stack. Qutiting\n");
      stackRemove(theStack);
      exit(0);
    }
  (newLayer)->message = message;
  (newLayer)->value = value;

  (newLayer)->lower = *theStack;
 
  *theStack = newLayer;

  return newLayer;
}

inline ErrorStack* stackPopS(ErrorStack** theStack)
{
  if(theStack == NULL || *theStack == NULL)
    {
      LOGE("Stack is Null\n");
      return NULL;
    }

  ErrorStack* lower = (*theStack)->lower;
  free(*theStack);
  *theStack = lower;
  return lower;
}


ErrorStack* stackPopV(ErrorStack** theStack)
{
  if(theStack == NULL || *theStack == NULL)
    {
      LOGE("Stack is Null\n");
      return NULL;
    }
  
  if((*theStack)->value == ERROR)
    {
      LOGE("%s\n", (*theStack)->message);
    }
  else
    {
      LOGN(stdout, "%s\n", (*theStack)->message);
    }

  return stackPopS(theStack);
}

ErrorStack* stackPopE(ErrorStack** theStack)
{
  if(theStack == NULL || *theStack == NULL)
    {
      LOGE("Error. The stack is Null\n");
      return NULL;
    }
  if((*theStack)->value == ERROR)
    {
      LOGE("%s\n", (*theStack)->message);
    }
  return stackPopS(theStack);
}

void stackDumpV(ErrorStack** theStack)
{
  if(theStack == NULL || *theStack == NULL)
    {
      LOGE("Error. Stack is null\n");
      return;
  }

  while((*theStack)->lower != NULL)
    {
      LOGD("Dump\n");
      stackPopV(theStack);
    }
  LOGD("Done\n");
}

void stackDumpE(ErrorStack** theStack)
{
  if(theStack == NULL || *theStack == NULL) return;
  while((*theStack)->lower != NULL)
    {
      stackPopE(theStack);
    }
}

void stackRemove(ErrorStack** theStack)
{
  if(theStack == NULL || *theStack == NULL) return;

  while((*theStack)->lower != NULL)
    {
      stackPopS(theStack);
    }
}




