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
	//root->value = new (String, "Root", 0);

	struct AbstractSyntaxTreeNode * parent = new (AbstractSyntaxTreeNode, 0);
	//parent->value = new (String, "Parent", 0);

	struct AbstractSyntaxTreeNode * uncle = new (AbstractSyntaxTreeNode, 0);
	//uncle->value = new (String, "Uncle", 0);

	struct AbstractSyntaxTreeNode * left = new (AbstractSyntaxTreeNode, 0);
	left->value = new (String, "Left", 0);

	struct AbstractSyntaxTreeNode * right = new (AbstractSyntaxTreeNode, 0);
	right->value = new (String, "Right", 0);
	
	ast->root = root;
	root->leftOperand = parent;
	root->rightOperand = uncle;
	parent->leftOperand = left;
	parent->rightOperand = right;

	printf("%s\n", toString(ast)->text);

	delete(ast);
	
	
	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}