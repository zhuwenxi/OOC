#include <stdio.h>
#include <stdlib.h>

#include "OOC.h"
#include "New.h"
#include "Object.h"
#include "Class.h"
#include "Point.h"
#include "Point_r.h"
#include "LinkList.h"
#include "LinkList_r.h"
#include "String.h"
#include "Set.h"
#include "HashTable.h"
#include "HashTable_r.h"
#include "Stack.h"
#include "Stack_r.h"
#include "Queue.h"
#include "Queue_r.h"
#include "AbstractSyntaxTree.h"
#include "AbstractSyntaxTree_r.h"




int main()
{	
	loadOoc();

	struct AbstractSyntaxTree * ast = new (AbstractSyntaxTree, 0);
	struct AbstractSyntaxTreeNode * root = new (AbstractSyntaxTreeNode, 0);

	ast->root = root;
	printf("%d\n", root->isLeaf);

	delete(ast);
	
	
	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}