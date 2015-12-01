#include <stdio.h>
#include <stdlib.h>

#include "Object.h"
#include "Class.h"
#include "Point.h"
#include "Point_r.h"
#include "OOC.h"

int main()
{	
	loadOoc();

	void * obj = new (Object, 0);

	printf("%s\n", toString(PointClass)->text);

	delete(obj);

	/*struct Point * point = new (Point, 1, 2);

	draw(point);

	delete(point);*/


	/*
	 * Pause here, to display the command-line output.
	 */
	system("pause");
}