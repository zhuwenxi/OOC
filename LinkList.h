#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdbool.h>

extern const void * LinkList;

extern const void * LinkListItem;
 
extern const void * ListClass;

void * listSearch(void * _self, void * _data);

bool listInsert(void * _self, void * _data);

bool listDelete(void * _self, void * _data);

void loadLinkList();

#endif