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




int main()
{	
	loadOoc();

	struct Stack * stack = new (Stack, 0);
	
	push(stack, new (String, "Alex", 0), 0);
	push(stack, new (String, "Bary", 0), 0);
	push(stack, new (String, "Cathy", 0), 0);
	
	printf("pop: %d\n", empty(stack));
	printf("%s\n", toString(stack)->text);

	delete(stack);
	/*struct Set * set = new (Set, 0);
	
	insert(set, new (String, "Alex", 0), 0);
	insert(set, new (String, "Bary", 0), 0);
	insert(set, new (String, "Cathy", 0), 0);
	insert(set, new (String, "Douglas", 0), 0);
	insert(set, new (String, "Ella", 0), 0);
	insert(set, new (String, "Frank", 0), 0);
	insert(set, new (String, "Gaven", 0), 0);
	insert(set, new (String, "Hill", 0), 0);
	insert(set, new (String, "Irving", 0), 0);

	erase(set, new (String, "Irving", 0), 0);
	printf("%s\n", toString(set)->text);

	delete(set);*/
	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}