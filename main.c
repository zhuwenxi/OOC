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




int main()
{	
	loadOoc();

	void * hashTable = new (HashTable, 0);

	insert(hashTable, new (String, "Apple", 0));
	insert(hashTable, new (String, "Banana", 0));
	insert(hashTable, new (String, "Cat", 0));

	printf("%s\n", toString(hashTable)->text);

	delete(hashTable);
	
	/*void * set = new (Set, 0);

	insert(set, new(String, "Apple"));
	insert(set, new(String, "Banana"));
	insert(set, new(String, "Cat"));

	printf("%s\n", toString(set)->text);

	delete(set);

	void * linkList = new(LinkList, 0);

	void * str1 = new (String, "Apple", 0);
	void * str2 = new (String, "Banana", 0);
	void * str3 = new (String, "Cat", 0);

	insert(linkList, str1);
	printf("%s\n", toString(linkList)->text);
	insert(linkList, str2);
	printf("%s\n", toString(linkList)->text);
	insert(linkList, str3);
	printf("%s\n", toString(linkList)->text);

	erase(linkList, str2);
	printf("%s\n", toString(linkList)->text);

	erase(linkList, str3);
	printf("%s\n", toString(linkList)->text);

	erase(linkList, str1);

	delete(linkList);*/

	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}