#ifndef __LIST_R_H__
#define __LIST_R_H__

#include <stdbool.h>
#include "Class_r.h"

struct List
{
	struct Class _;
	void * (*listSearch)(void * _list, void * _data);
	bool(*listInsert)(void * _list, void * _data);
	bool(*listDelete)(void * _list, void * _data);
	bool(*insertAt)(void * _list, void * _data, int index);
};

#endif