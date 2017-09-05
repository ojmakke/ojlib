#include "../ojlogger/ojlogger.h"
#include "../ojllist/ojllist.h"
#include "../ojmemory/ojmemory.h"
#include "ojast.h"

#include <string.h>
#include <assert.h>

#define DELIMITER ';'
#define LP '('
#define RP ')'

void printTree(struct OjAST const* tree, int num)
{
  int ii;
  int jj;
  for(ii = 0; ii < num; ii++)
    printf("   ");
  
  LOGD("%s\n", tree->root);
  //  printf("%s\n", tree->children[0].root);
  for(ii = 0; ii < tree->numChildren; ii++ )
    {
      printTree(&(tree->children[ii]), num+1);
    }
}


// Given a lispy string, get the root string.
// Example: a(b, c(d, e, f)) returns a
// Example (b, c(d, e, f)) returns c
// String is allocated on provided heap block
char* get_ojast_root(struct HeapBlock* heap, char* lispy)
{
  LOGD("***get_ojast_root***\n");
  assert(heap != NULL);
  assert( lispy != NULL);
  
  int ii = 0;
  // Search for ( in string
  while(lispy[ii] != 0)
    {
      if(lispy[ii] == LP)
	{
	  break;
	}
      ii++;
    }

  if(ii == 0)
    {
      return NULL; // no root found. String starts with ()
    }

  int size = ii+1;
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
// Skip until the num-1 delimiter and read until either end of balanced ), or end of line
// Assume num starts at 0
char* get_ojast_param(struct HeapBlock* heap, char* lispy, int num)
{
  LOGD("***get_ojast_param***\n");
  int ii = 0;
  int lp = 0;
  int rp = 0;
  int beginIndex = 0; // beginning of parameter
  int endIndex = 0; // end of parameter
  int paramFound = 0;
  char* retValue = NULL;
  LOGD("lispy is %s\n", lispy);
  
  ii = 0;
  lp = 0;
  rp = 0;
  // Don't do anything until LP is found. Then find next delimiter or balanced paran.
  // Then return what is found.
  while(lispy[ii] != 0)
    {
      // Keep moving the end index until done
      endIndex = ii;

      // find the weight of the ()
      if(lispy[ii] == LP)
	{
	  lp++;
	}
      else if(lispy[ii] == RP)
	{
	  rp++;
	}

      // If both are > 0 and lp > 1 means that brackets are full.
      if(lp - rp == 0 && lp > 1)
	{
	  //	  LOGD("End\n");
	  endIndex = ii; // The ) will be replaced by 0
	  break;
	}
      // Only 1 level We are in a parameter.
      else if(lispy[ii] == DELIMITER && lp-rp == 1)
	{
	  //	  LOGD("1 level\n");
	  if(paramFound == num)
	    {
	      endIndex = ii; // The ) will be repalced by 0
	      break;
	    }
	  else
	    {
	      paramFound++;
	      beginIndex = ii+1; // Next parameter starts after delimiter.
	    }
	}
      else if(lp - rp == 1 && lispy[ii] == LP)
	{
	  //	  LOGD("Begin\n");
	  beginIndex = ii+1; // Do not include (
	}
      ii++;
    }
  
  printf("(--%d, %d, %d, %d)\n", beginIndex, endIndex, paramFound, num);
  assert(beginIndex < endIndex);
  // We add 1: since a string () has length 2,
  // but end - begin = 1
  int strSize = endIndex - beginIndex + 1;
  retValue = oj_heap_malloc(heap, strSize);
  for(ii = 0; ii < strSize; ii++)
  {
    retValue[ii] = lispy[ii+beginIndex];
  }
  retValue[strSize-1] = 0; // End with terminating null
  LOGD("Parameter is %s\n", retValue);

  return retValue;;
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
				 struct OjAST* parent)
{
  LOGD("***oj_ast_parseString***\n");
  // lispy is oj_lisp style. Example: a(b(c,d),e,f(g)), not (a (b (c d) ) e (f g))
  // Only the first root can be empty: (b(c,d),e,f(g))
  // It is expected to pass a lispy parameter:
  int ii = 0;
  int lp = 0;
  int rp = 0;
  int size = 0;
  // Add a lot more error checking.
  // For now, assume delimiter is used correctly
  // No ,) or ), or ),) ...
  parent->root = get_ojast_root(heap, lispy);
  LOGD("Root is: %s\n", parent->root);

  // Find breadth of the level. Find delimiters where open brackets = 1
  // In the end, if size was 1, then there are no parameters
  ii = 0;
  lp = 0;
  while(lispy[ii] != 0)
    {
      if(lispy[ii] == LP)
	{
	  lp++;
	}
      else if(lispy[ii] == RP)
	{
	  rp++;
	}
      // Only 1 level 
      if(lispy[ii] == DELIMITER && lp-rp == 1)
	{
	  size++;
	}
      else if(lispy[ii] == RP && lp-rp == 0)
	{
	  size++;
	}
      ii++;
    }
  //  size++; // No comma after last parameter (which can be first parameter too)
  parent->numChildren = size;
  if(size == 0)
    {
      // No parameters. Return with this as the parameter.
      parent->children = NULL;
      return parent;
    }

  // Now we know the breadth size. Allocate memory, and create tree for depth, recursively
  parent->children = oj_heap_malloc(heap, size*sizeof(struct OjAST));

  for(ii = 0; ii < size; ii++)
    {
      // get the ith parameter.
      char* param = get_ojast_param(heap, lispy, ii);
      assert(param != NULL); // because size is # of parameters, should never be.
      // note that parent->children[ii] is already allocated.
      parent->children[ii] = *oj_ast_parseString(heap, param, &(parent->children[ii]));
    }

  return parent;
}
struct OjAST* oj_ast_getSubTree(struct OjAST* superTree);

