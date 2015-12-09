#ifndef __ITERATOR_H__
#define __ITERATOR_H__




#include "Object_r.h"
#include "Iterator.h"

extern const void * Iterator;

extern const void * IteratorClass;

void loadIterator();


struct Iterator * start(struct Iterator * iter);

struct Iterator * end(struct Iterator * iter);

struct Iterator * next(struct Iterator * iter);

#endif