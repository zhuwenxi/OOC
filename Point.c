#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

#include "Class.h"
#include "Class_r.h"
#include "Object.h"
#include "Object_r.h"
#include "Point.h"
#include "Point_r.h"

static void * Point_ctor(void * _self, va_list * args)
{
	struct Point * self = super_ctor(Point, _self, args);

	self->x = va_arg(*args, int);
	self->y = va_arg(*args, int);

	return self;
}

static void * PointClass_ctor(void * _self, va_list * args)
{
	struct PointClass * self = super_ctor(PointClass, _self, args);
	typedef void (*voidf)();
	voidf selector;
	va_list arg = *args;

	while ((selector = va_arg(arg, voidf)))
	{
		voidf method = va_arg(arg, voidf);

		if (selector == draw)
		{
			self->draw = method;
		}
	}

	return self;
}

static void Point_draw(const void * _self)
{
	const struct Point * self = _self;
	printf("draw: %d,%d\n", self->x, self->y);
}

void draw(const void * _self)
{
	const struct PointClass ** self = _self;

	(*self)->draw(_self);
}


const void * Point;

const void * PointClass;

void loadPoint()
{
	if (!PointClass)
	{
		PointClass = new (Class, "PointClass", Class, sizeof(struct PointClass), ctor, PointClass_ctor, 0);

	}

	if (!Point)
	{
		Point = new(PointClass, "Point", Object, sizeof(struct Point), ctor, Point_ctor, draw, Point_draw, 0);
	}
}