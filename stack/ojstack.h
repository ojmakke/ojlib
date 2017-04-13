#ifndef OJSTACK_H
#define OJSTACK_H

enum StackEnumsDef
  {
    NOTSET,
    SUCCESS,
    ERROR,
    WARNING,
    UNKOWN,
  };
typedef enum StackEnumsDef StackEnums;

struct ErrorStack
{
  char* message;
  StackEnums value;
  struct ErrorStackDef* lower;
};

typedef struct ErrorStack ErrorStack;


/* This returns a new stack variable */
extern ErrorStack makeNewStack();

/* Add to stack */
extern ErrorStack* stackPush(ErrorStack** theStack, char* message, StackEnums value);

/* Pop the value from stack and print message */
extern ErrorStack* stackPopV(ErrorStack** theStack);

/* Pops and writes to stderr the error message if it is not SUCCESS */ 
extern ErrorStack* stackPopE(ErrorStack** theStack);

/* Pops the value from the stack silently (removes it)*/
extern inline ErrorStack* stackPopS(ErrorStack** theStack);

extern void stackDumpV(ErrorStack** theStack);
extern void stackDumpE(ErrorStack** theStack);
extern void stackRemove(ErrorStack** theStack);

#endif
