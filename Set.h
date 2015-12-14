#ifndef __SET_H__
#define __SET_H__

#include "List.h"
#include "Iterator.h"

extern const void * Set;

extern const void * SetIterator;

bool swap(void * self, int one, int another);
int indexOf(void * self, void * token);

void loadSet();

#endif