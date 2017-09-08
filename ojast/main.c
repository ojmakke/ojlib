#include <stdio.h>
#include <string.h>

#include "ojast.h"
#include "../ojlogger/ojlogger.h"
#include "../ojmemory/ojmemory.h"

// buffer size
#define BSIZE 4096
#define SUCCESS 1
#define FAILURE 2

int verify_syntax(char* str, int len)
{
  int ii;
  int lp, rp; // counter for left paranthesis and right.

  // str[len-1] should be the terminating null.
  lp = 0; rp = 0;

  if(len == 0 || str[0] != '(' || str[len-1] != ')')
    {
      LOGE("Check Boundaries for %s\n", str);
      //    return FAILURE;
    }

  
  for(ii = 0; ii < len; ii++)
    {
      if( str[ii] == ')')
	{
	  rp++;
	}

      // rp should never be > lp
      if(rp > lp)
	{
	  LOGE("Error. Check paranthesis at %d\n", ii);
	  return FAILURE;
	}

      if(str[ii] == '(')
	{
	  lp++;
	}
    }
  if(lp != rp)
    {
      LOGE("Error. Left and right paranthesis are not balanced.\n");
      return FAILURE;
    }

  LOGD("String %s is analyzed \n", str);
  return SUCCESS;
 
}


int main(int argc, char* argv[])
{
  struct HeapBlock* astHeap;
  int ii;
  int stringLen;
  char bufferString[BSIZE];
  char* param;

  if(argc != 2)
    {
      LOGE("Must pass a lispy parameter as 1 argument between \"\"\n");
      return -1;
    }

  memset(bufferString, 0, BSIZE );
  // Make sure that argument fits in 4kb
  ii = 0;
  param = argv[1];
  
  while(param[ii] != 0)
    {
      ii++;
    }

  if(ii >=  BSIZE)
    {
      LOGE("Argument string is too large, greater than %d\n", BSIZE);
      return -1;
    }

  stringLen = ii;

  // Simple error checking. Make sure ( matches ) and correct
  if( verify_syntax(argv[1], stringLen) != SUCCESS )
    {
      LOGE("In string: %s of length %d\n", argv[1], stringLen);
      LOGE("Incorrect sytax. Check paranthesis\n");
      return -1;
    }

  astHeap =  oj_heap_create();
  struct OjAST* ast = oj_heap_malloc(astHeap, sizeof(struct OjAST));
  ast->children = NULL;
  ast->root = NULL;
  LOGD("Parsing ast for %s\n", argv[1]);
  ast = oj_ast_parseString(astHeap, argv[1], ast);

  printTree(ast,1);


  return 0;
}


