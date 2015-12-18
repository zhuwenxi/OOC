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




int main()
{	
	loadOoc();

	/*struct String * key = new (String, "KEY", 0);
	struct String * value = new (String, "VALUE", 0);
	struct Pair * pair = new(Pair, key, value, 0);

	struct String * keyText = toString(pair->key);
	struct String * valueText = toString(pair->value);

	printf("%s, %s\n", keyText->text, valueText->text);

	delete(pair);*/
	
	struct Pair * apple = new (Pair, new(String, "Apple", 0), new(String, "Red", 0), 0);
	struct Pair * banana = new (Pair, new(String, "Banana", 0), new (String, "Yellow", 0), 0);
	struct Pair * cat = new (Pair, new(String, "Cat", 0), new (String, "White", 0), 0);

	void * hashTable = new (HashTable, 0);

	insert(hashTable, apple);
	insert(hashTable, banana);
	insert(hashTable, cat);

	struct String * string = toString(hashTable);
	printf("%s\n", string->text);

	erase(hashTable, new (String, "Banana", 0));
	erase(hashTable, new (String, "Apple", 0));
	erase(hashTable, new (String, "Cat", 0));

	delete(hashTable);

	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}