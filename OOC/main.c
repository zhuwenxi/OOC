#include <stdio.h>
#include <stdlib.h>

#include "Object.h"
#include "Class.h"
#include "Point.h"
#include "Point_r.h"

void * test_ctor(void * self, va_list *args)
{
	printf("test_ctor\n");
	return self;
}

int main()
{	
	initPoint();

	printf("===================================\n");

	struct Point * point = new (Point, 1, 2);

	draw(point);

	delete(point);
	//printf("%s\n", ((struct Class *)Point)->super->name);

	/*printf("%d\n", ((struct Class *)Class)->super == Object);
	printf("%d\n", ((struct Class *)Object)->super == Object);*/

	// printf("%p\n", ((struct Class *)PointClass)->super);


	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}