#ifndef __QUEUE_H__
#define __QUEUE_H__




extern const void * Queue;
extern const void * QueueClass;




void * enqueue(void * self, void * element);
void * dequeue(void * self);
void * unshift(void * self);

void loadDequeue();


#endif