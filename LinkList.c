#include <stdarg.h>
#include <assert.h>

#include "LinkList.h"
#include "LinkList_r.h"
#include "Object.h"
#include "Object_r.h"
#include "Class.h"
#include "New.h"

/*
 * LinkList:
 */
static void * LinkList_dtor(void * _self)
{
	struct LinkList * self = cast(LinkList, _self);
	struct LinkListItem * head = self->head;
	struct LinkListItem * next = head;
	
	while (next != NULL)
	{
		struct LinkListItem * temp = next;
		next = next->next;

		delete(temp);
	}

	return self;
}

static void * LinkList_search(void * _self, void * _data)
{
	struct LinkList * self = cast(LinkList, _self);
	struct LinkListItem * head = cast(LinkListItem, self->head);
	struct LinkListItem * next;
	struct Object * data;

	if (head != NULL)
	{
		next = head;

		while (next != NULL)
		{
			data = next->data;

			if (equals(data, _data))
			{
				return next;
			}

			next = next->next;
		}
	}

	return NULL;
}

static bool LinkList_insert(void * _self, void * _data)
{
	struct LinkList * self = cast(LinkList, _self);
	struct LinkListItem * head = cast(LinkListItem, self->head);
	struct LinkListItem * newElement;
	struct LinkListItem * next = head;

	if (self != NULL)
	{
		newElement = new (LinkListItem, _data, 0);

		if (head == NULL)
		{
			self->head = newElement;
		}
		else
		{
			next = head;
			while (next->next != NULL)
			{
				next = next->next;
			}

			next->next = newElement;

			newElement->prev = next;
		}

		return true;
	}
	else
	{
		return false;
	}
	
	
}

static bool LinkList_delete(void * _self, void * _data)
{
	struct LinkList * self = cast(LinkList, _self);
	struct LinkListItem * head = cast(LinkListItem, self->head);
	struct LinkListItem * found = LinkList_search(_self, _data);

	struct LinkListItem * prev;
	struct LinkListItem * next;


	if (found != NULL)
	{	
		
		prev = found->prev;
		next = found->next;

		if (found == head)
		{
			self->head = next;
		}

		if (prev != NULL)
		{
			prev->next = next;
		}

		if (next != NULL)
		{
			next->prev = prev;
		}

		delete(found);
	}
	else
	{
		return true;
	}
}

/*
 * LinkListItem:
 */

static void * LinkListItem_ctor(void * _self, va_list * args)
{
	struct LinkListItem * self = cast(LinkListItem, _self);

	self->data = va_arg(*args, struct Object *);

	return self;
}

static void * LinkListItem_dtor(void * _self)
{
	struct LinkListItem * self = cast(LinkListItem, _self);
	struct Object * data = self->data;

	delete(data);

	return self;
}

/*
 * ListClass:
 */

static void * ListClass_ctor(void * _self, va_list * _args)
{
	struct ListClass * self = super_ctor(ListClass, _self, _args);
	typedef void(*voidf)();
	voidf selector;
	va_list args = *_args;

	while ((selector = va_arg(args, voidf)) != 0)
	{
		voidf method = va_arg(args, voidf);

		if (selector == listSearch)
		{
			self->listSearch = method;
		} 
		else if (selector == listInsert)
		{
			self->listInsert = method;
		}
		else if (selector == listDelete)
		{
			self->listDelete = method;
		}
	}

	return self;

}

void * listSearch(void * _self, void * _data)
{
	const struct Object * self = cast(Object, _self);
	const struct ListClass * class = cast(ListClass, self->class);

	if (class)
	{
		return class->listSearch(_self, _data);
	}
	else
	{
		return NULL;
	}

}

bool listInsert(void * _self, void * _data)
{
	const struct Object * self = cast(Object, _self);
	const struct ListClass * class = cast(ListClass, self->class);

	if (class)
	{
		return class->listInsert(_self, _data);
	}
	else
	{
		return false;
	}
}

bool listDelete(void * _self, void * _data)
{
	const struct Object * self = cast(Object, _self);
	const struct ListClass * class = cast(ListClass, self->class);

	if (class)
	{
		return class->listDelete(_self, _data);
	}
	else
	{
		return false;
	}
}


const void * LinkList;

const void * LinkListItem;

const void * ListClass;

void loadLinkList()
{
	if (!ListClass)
	{
		ListClass = new (Class, "ListClass", Class, sizeof(struct ListClass), ctor, ListClass_ctor, 0);
	}

	if (!LinkList)
	{
		LinkList = new (ListClass, "LinkList", Object, sizeof(struct LinkList), dtor, LinkList_dtor, listSearch, LinkList_search, listInsert, LinkList_insert, listDelete, LinkList_delete, 0);
	}

	if (!LinkListItem)
	{
		LinkListItem = new (Class, "LinkListItem", Object, sizeof(struct LinkListItem), ctor, LinkListItem_ctor, dtor, LinkListItem_dtor, 0);
	}
}