#ifndef __ITERATOR_R_H__
#define __ITERATOR_R_H__




#include "Object_r.h"
#include "Class_r.h"

struct Iterator
{
	struct Object _;
	struct Object * data;
	int index;
};

struct IteratorClass
{
	struct Class _;
	struct Object * (*start)(const struct Iterator * iter);
	struct Object * (*end)(const struct Iterator * iter);
	struct Object * (*next)(const struct Iterator * iter);
};


#endif