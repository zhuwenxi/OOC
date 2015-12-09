#ifndef __SET_R__
#define __SET_R__

#include "Object_r.h"
#include "Class_r.h"
#include "Iterator_r.h"

struct Set
{
	struct Object _;
	void ** items;
	int length;
	int capacity;
};

struct SetIterator
{
	struct Iterator _;
};

#endif