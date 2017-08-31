#include "../ojlogger/ojlogger.h"
#include "../ojllist/ojllist.h"
#include "../ojmemory/ojmemory.h"

struct OjAST
{
  char* root; 	// Name of the root
  struct OjAST* children; // Children nodes 
};

struct OjAST* oj_ast_parseString(struct HeapBlock* heap,
				 char* lispy,
				 struct OjAST* allocated_parent
				 );
struct OjAST* oj_ast_getSubTree(struct OjAST* superTree);
