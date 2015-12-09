#ifndef __ITERATOR_H__
#define __ITERATOR_H__




#include "Object_r.h"
#include "Iterator.h"

extern const void * Iterator;

extern const void * IteratorClass;

void loadIterator();


struct Object * start(const struct Iterator * iter);

struct Object * end(const struct Iterator * iter);

struct Object * next(const struct Iterator * iter);

#endif