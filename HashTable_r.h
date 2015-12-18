#ifndef __HASHTABLE_R_H__
#define __HASHTABLE_R_H__

#include "Object_r.h"
#include "LinkList_r.h"

struct HashTable
{
	struct Object _;
	struct LinkList ** slots;
};

struct Pair
{
	struct Object _;
	void * key;
	void * value;
};

#endif