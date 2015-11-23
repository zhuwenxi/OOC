#include <stdio.h>
#include <stdlib.h>

#include "Object.h"
#include "Class.h"

int main()
{	
	printf("name: %s\n", ((struct Class *)Object)->name);
	printf("name: %s\n", ((struct Class *)Class)->name);
	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}