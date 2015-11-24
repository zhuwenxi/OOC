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
	set_debug_tag(false);
	initPoint();

	struct Point * point = new (Point, 1, 2);

	// draw(point);
	printf("%d\n", isOf(Point, Object));

	delete(point);


	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}