#ifndef __LINKLIST_R_H__
#define __LINKLIST_R_H__

#include <stdbool.h>

#include "Object_r.h"
#include "Class_r.h"

struct LinkList
{
	struct Object _;
	struct LinkListItem * head;
};

struct LinkListItem
{
	struct Object _;
	struct LinkListItem * prev;
	struct LinkListItem * next;
	struct Object * data;
};

#endif