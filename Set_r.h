#ifndef __SET_R__
#define __SET_R__

#include "Object_r.h"
#include "Class_r.h"

struct Set
{
	struct Object _;
	void ** items;
	int length;
	int capacity;
};

struct SetClass
{
	struct Class _;
	void * (*add)(void * self, void * item);
};

//struct SetItem
//{
//	struct Object _;
//	void * data;
//};

#endif