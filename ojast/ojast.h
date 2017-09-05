#include "../ojlogger/ojlogger.h"
#include "../ojllist/ojllist.h"
#include "../ojmemory/ojmemory.h"

struct OjAST
{
  struct OjAST* children; // Children nodes
  char* root;
  int numChildren;
};

struct OjAST* oj_ast_parseString(struct HeapBlock* heap,
				 char* lispy,
				 struct OjAST* allocated_parent
				 );
struct OjAST* oj_ast_getSubTree(struct OjAST* superTree);

void printTree(struct OjAST const *  tree, int num);
