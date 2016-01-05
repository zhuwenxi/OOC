#ifndef __QUEUE_R_H__
#define __QUEUE_R_H__




#include "Object_r.h"
#include "Class_r.h"
#include "LinkList_r.h"




struct Queue
{
	struct Object _;
	struct LinkList * _queue;
};

struct QueueClass
{
	struct Class _;
	void * (*enqueue)(void * self, void * element);
	void * (*dequeue)(void * self);
	void * (*unshift)(void * self, void * element);
};

#endif