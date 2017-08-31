#include "../ojlogger/ojlogger.h"
#include "../ojllist/ojllist.h"
#include "../ojmemory/ojmemory.h"
#include "ojast.h"

#include <string.h>
#include <assert.h>

#define DELIMITER ';'
#define LP '('
#define RP ')'


// Given a lispy string, get the root string.
// Example: a(b, c(d, e, f)) returns a
// Example (b, c(d, e, f)) returns c
// String is allocated on provided heap block
char* get_ojast_root(struct HeapBlock* heap, char* lispy)
{
  LOGD("***get_ojast_root***\n");
  int ii = 0;
  while(lispy[ii] != 0)
    {
      ii++;
      if(lispy[ii] == LP)
	{
	  break;
	}
    }

  if(ii == 0)
    {
      return NULL; // no root found. Lispy is either null or starts with ()
    }
  
  int size = ii;
  char* root = oj_heap_malloc(heap, size);
  assert(root != NULL);
  
  for(ii = 0; ii < size; ii++)
    {
      root[ii] = lispy[ii];
    }
  root[size-1] = 0; // terminating null;
  return root;
}

// Given a lispy string, get the parameter number num.
// if it doesn't exist, return null
char* get_ojast_param(char* lispy, int num)
{

  return NULL;
}


// Input: oj_lisp style string.
// Heap to allocate memory to
// allocated but not initialized parent.
// Output:
// Abstract Syntax Tree.
// Note that a call to this function is recursive. Each recurrance populates:
// - The root of the parent
// - allocates the children, but does not initialize
// - calls recursion on children, so each child becomes parent.

struct OjAST* oj_ast_parseString(struct HeapBlock* heap,
				 char* lispy,
				 struct OjAST* allocated_parent)
{
  LOGD("***oj_ast_parseString***\n");
  // lispy is oj_lisp style. Example: a(b(c,d),e,f(g)), not (a (b (c d) ) e (f g))
  // Only the first root can be empty: (b(c,d),e,f(g))
  // It is expected to pass a lispy parameter:
  struct OjAST* parent; //alias to allocated_parent, easy typing
  int ii = 0;
  int lp = 0;
  int size = 0;
  // Add a lot more error checking.
  // For now, assume delimiter is used correctly
  // No ,) or ), or ),) ...
  parent = allocated_parent;
  parent->root = get_ojast_root(heap, lispy);

  // Find breadth of the level. Find delimiters where open brackets = 1
  // In the end, if size was 1, then there are no parameters
  while(lispy[ii] != 0)
    {
      if(lispy[ii] == LP)
	{
	  lp++;
	}
      else if(lispy[ii] == RP)
	{
	  lp--;
	}
      // Only 1 level 
      else if(lispy[ii] == DELIMITER && lp == 1)
	{
	  size++;
	}
      ii++;
    }
  size++; // No comma after last parameter (which can be first parameter too)
  if(size == 1)
    {
      // No parameters. Return with this as the parameter.
      parent->children = NULL;
      return parent;
    }

  // Now we know the breadth size. Allocate memory, and create tree for depth, recursively
  parent->children = oj_heap_malloc(heap, size*sizeof(struct OjAST));
 
  for(ii = 0; ii < size; ii++)
    {
    
    }
  printf("Name is: %s\n", parent->root);
  
  return 0;
}
struct OjAST* oj_ast_getSubTree(struct OjAST* superTree);

