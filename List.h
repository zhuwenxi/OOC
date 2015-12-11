#ifndef __LIST_H__
#define __LIST_H__

/*
 * "List" is an abstract base class, "LinkList" and "HashTable" are derived from this class.
 * TO DO: refactor the "Set" class, make it derived from "List".
 */
#include <stdbool.h>

extern const void * List;

void * search(void * _self, void * _data);

bool insert(void * _self, void * _data);

bool erase(void * _self, void * _data);

bool insertAt(void * _self , void * _data, int index);

void merge(void * self, void * another, ...);


void loadList();

#endif