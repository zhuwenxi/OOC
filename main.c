#include <stdio.h>
#include <stdlib.h>

#include "OOC.h"
#include "Object.h"
#include "Class.h"
#include "Point.h"
#include "Point_r.h"
#include "LinkList.h"
#include "LinkList_r.h"
#include "String.h"




int main()
{	
	loadOoc();

	void * linkList = new(LinkList, 0);

	void * str1 = new (String, "Apple", 0);
	void * str2 = new (String, "Banana", 0);
	void * str3 = new (String, "Cat", 0);

	insert(linkList, str1);
	insert(linkList, str2);
	insert(linkList, str3);

	delete(linkList);

	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}