#include "Queue.h"
#include "Queue_r.h"
#include "Class.h"
#include "Object.h"
#include "LinkList.h"
#include "LinkList_r.h"

#include <stdarg.h>
#include <assert.h>




void * enqueue(void * _self, void * _element)
{
	struct QueueClass * class = classOf(_self);

	assert(class);

	return class->enqueue(_self, _element);
}

void * dequeue(void * _self)
{
	struct QueueClass * class = classOf(_self);

	assert(class);

	return class->dequeue(_self);
}

void * unshift(void * _self, void * _element)
{
	struct QueueClass * class = classOf(_self);
	assert(class);

	return class->unshift(_self, _element);
}

void * Queue_ctor(void * _self, va_list * args)
{
	struct Queue * self = cast(Queue, _self);
	assert(self);
	
	self->_queue = new (LinkList, 0);

	return _self;
}

void * Queue_dtor(void * _self)
{
	struct Queue * self = cast(Queue, _self);
	assert(self);

	delete(self->_queue);

	return _self;
}

void * Queue_enqueue(void * _self, void * _element)
{
	struct Queue * self = cast(Queue, _self);
	assert(self);

	insert(self->_queue, _element);

	return _element;
}

void * Queue_dequeue(void * _self)
{
	struct Queue * self = cast(Queue, _self);
	assert(self);

	struct LinkList * _queue = cast(LinkList, self->_queue);
	assert(_queue);

	struct LinkListItem * next = _queue->head;

	if (!next)
	{
		return NULL;
	}
	else
	{
		while (next->next)
		{
			next = next->next;
		}

		assert(next);

		void * data = next->data;
		void * retData = clone(data);

		erase(_queue, data);

		return retData;
	}
}

void * Queue_unshift(void * _self, void * _element)
{
	struct Queue * self = cast(Queue, _self);
	assert(self);

	struct LinkList * _queue = cast(LinkList, self->_queue);
	assert(_queue);

	struct LinkListItem * newElement = new (LinkListItem, _element, 0);

	if (_queue->head)
	{
		struct LinkListItem * next = _queue->head;

		_queue->head = newElement;
		newElement->next = next;
		newElement->prev = NULL;
		
		next->prev = newElement;
	}
	else
	{
		_queue->head = newElement;
		newElement->prev = NULL;
		newElement->next = NULL;
	}
}

void * Queue_toString(void * _self)
{
	struct Queue * self = cast(Queue, _self);
	assert(self);

	struct LinkList * _queue = cast(LinkList, self->_queue);
	assert(_queue);

	return toString(_queue);
}

void * QueueClass_ctor(void * _self, va_list * args)
{
	struct QueueClass * self = super_ctor(QueueClass, _self, args);
	assert(self);

	va_list arg = *args;

	typedef (*voidf)();
	voidf selector;
	voidf method;

	while ((selector = va_arg(arg, voidf)) != 0)
	{
		method = va_arg(arg, voidf);
		
		if (selector == enqueue)
		{
			self->enqueue = method;
		}
		else if (selector == dequeue)
		{
			self->dequeue = method;
		}
		else if (selector == unshift)
		{
			self->unshift = method;
		}
	}

	return _self;
}




const void * Queue;
const void * QueueClass;

void loadQueue()
{
	if (!QueueClass)
	{
		QueueClass = new (Class, "QueueClass", Class, sizeof(struct QueueClass), ctor, QueueClass_ctor, 0);
	}

	if (!Queue)
	{
		Queue = new (QueueClass, "Queue", Object, sizeof(struct Queue), ctor, Queue_ctor, dtor, Queue_dtor, toString, Queue_toString, enqueue, Queue_enqueue, dequeue, Queue_dequeue, unshift, Queue_unshift, 0);
	}
}