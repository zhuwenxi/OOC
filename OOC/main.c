#include <stdio.h>
#include <stdlib.h>

#include "Object.h"
#include "Class.h"

int main()
{	
	void * obj = new (Object);
	void * cls = new (Class);
	
	delete(obj);
	delete(cls);

	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}