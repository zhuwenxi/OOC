#ifndef __POINT_R_H__
#define __POINT_R_H__

#include "Object_r.h"
#include "Class_r.h"

struct Point
{
	struct Object _;
	int x;
	int y;
};

struct PointClass
{
	struct Class _;
	void(*draw)(const void *self);
};


#endif