#include <stdarg.h>
#include <assert.h>

#include "List.h"
#include "List_r.h"
#include "LinkList.h"
#include "LinkList_r.h"
#include "Object.h"
#include "Object_r.h"
#include "Class.h"
#include "New.h"
#include "String.h"
#include "String_r.h"

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

static struct String * LinkList_toString(const void * self)
{
	const struct LinkList * list = cast(LinkList, self);
	const struct LinkListItem * head;
	const struct LinkListItem * next;
	struct String * retVal;

	struct String * temp;
	struct String * space;
	struct String * property;
	
	if (list)
	{
		head = cast(LinkListItem, list->head);

		if (head)
		{
			next = head;

			retVal = new (String, "", 0);

			while (next)
			{
				
				temp = retVal;
				space = new (String, " ", 0);
				property = toString(next->data);

				if (property)
				{ 
					retVal = add(retVal, property, space, 0);
				}
				
				delete(property);
				delete(temp);
				delete(space);

				next = next->next;
			}

			return retVal;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
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


const void * LinkList;

const void * LinkListItem;

void loadLinkList()
{
	if (!LinkList)
	{
		LinkList = new (List, "LinkList", Object, sizeof(struct LinkList), dtor, LinkList_dtor, search, LinkList_search, insert, LinkList_insert, erase, LinkList_delete, toString, LinkList_toString,0);
	}

	if (!LinkListItem)
	{
		LinkListItem = new (Class, "LinkListItem", Object, sizeof(struct LinkListItem), ctor, LinkListItem_ctor, dtor, LinkListItem_dtor, 0);
	}
}