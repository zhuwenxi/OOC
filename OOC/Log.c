#include "Log.h"

#include "stdio.h"

static bool debug_tag = true;

void set_debug_tag(bool tag)
{
	debug_tag = tag;
}

void log(char *msg)
{
	printf(msg);
}