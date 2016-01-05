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




int main()
{	
	loadOoc();

	struct Queue * q = new (Queue, 0);

	enqueue(q, new (String, "Alex", 0), 0);
	enqueue(q, new (String, "Bary", 0), 0);
	enqueue(q, new (String, "Cathy", 0), 0);

	printf("%s\n", toString(q)->text);

	dequeue(q);
	printf("%s\n", toString(q)->text);

	dequeue(q);
	printf("%s\n", toString(q)->text);

	dequeue(q);
	dequeue(q);
	dequeue(q);
	printf("%p\n", toString(q));

	delete(q);
	/*struct Stack * stack = new (Stack, 0);
	
	push(stack, new (String, "Alex", 0), 0);
	push(stack, new (String, "Bary", 0), 0);
	push(stack, new (String, "Cathy", 0), 0);
	
	printf("pop: %d\n", empty(stack));
	printf("%s\n", toString(stack)->text);

	delete(stack);*/
	
	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}