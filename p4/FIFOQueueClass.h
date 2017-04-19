#ifndef _TEMPLATE_FIFO_QUEUE_CLASS_
#define _TEMPLATE_FIFO_QUEUE_CLASS_
#include "LinkedNodeClass.h"

/* HEADER: FIFOQueueClass is a special 'first-in'first-out' queue
that riders enter while waiting for the line. The functionality
of the FIFO is mainly enqueuing and dequeueing riders. To help with
the simulation, it also can return the number of nodes in the FIFO
and print out the value of the nodes
*/

template < class T >
class FIFOQueueClass
{
private:
  LinkedNodeClass< T > *head;
  LinkedNodeClass< T > *tail;

public:
  FIFOQueueClass(); // initialize to empty queue

  void enqueue(const T &newItem);

  bool dequeue(T &outItem);

  void print() const;

  int getNumElems() const;

};



#include "FIFOQueueClass.inl"
#endif