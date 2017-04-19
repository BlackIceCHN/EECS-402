#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
#include <iostream>
#include <cstdlib>
using namespace std;

/* HEADER: The implementation of FIFOQueueClass. A more thorough 
description can be found in FIFOQueueClass.h
*/


// default ctor - creates empty FIFO line
template < class T >
FIFOQueueClass < T >::FIFOQueueClass()
{
  head = NULL;
  tail = NULL;
}


// getNumElems() - returns the number of elements (riders) in a FIFO line
template < class T >
int FIFOQueueClass < T >::getNumElems() const
{
  int numElems = 0;
  // start at first node
  LinkedNodeClass < T >* tempPtr = head;
  while (tempPtr != NULL)
  {
    numElems += 1;
    // go to next node
    tempPtr = tempPtr->getNext();
  }

  return numElems; 
}


/* enqueue(const T &newItem) - Inserts the value provided (newItem)
into the queue. Adjusts head and/or tail accordingly
*/
template < class T >
void FIFOQueueClass < T >::enqueue(const T &newItem)
{
  //LinkedNodeClass< T >* tempPtr = head;
  LinkedNodeClass < T >* newNode;

  if (tail == NULL) // if list is empty
  {
    // make new node
    newNode = new LinkedNodeClass< T >(NULL, newItem, NULL);
    // have head and tail point to it
    head = newNode;
    tail = newNode;
    //cout << "value of added node is: " << newNode->getValue() << endl;
  }
  else
  {
    newNode = new LinkedNodeClass< T >(NULL, newItem, head);
    head = newNode;
    newNode->setBeforeAndAfterPointers();
  }
}


// deque(T &outItem) - Attempts to take the next item out of the queue. If the
// queue is empty, the function returns false and the state
// of the reference parameter (outItem) is undefined. If the
// queue is not empty, the function returns true and outItem
// becomes a copy of the next item in the queue, which is
// removed from the data structure.
template < class T >
bool FIFOQueueClass < T >::dequeue(T &outItem)
{
  LinkedNodeClass < T >* tempPtr;
  bool success = true;
  // if empty
  if (tail == NULL)
  {
    success = false;
  }
  else
  {
    tempPtr = tail;

    outItem = tempPtr->getValue();
    // if there is only one node in the list
    if (tempPtr->getPrev() == NULL)
    {
      tail = tempPtr->getPrev();
      head = tempPtr->getNext();
    }
    else
    {
      tail = tempPtr->getPrev();
      // set previous node to point to NULL
      tempPtr->setPreviousPointerToNull();
    }
    // free memory
    delete tempPtr;

  }

  return success;
}

// print() - Prints out the contents of the queue. All printing is done
// on one line, using a single space to separate values, and a
// single newline character is printed at the end.
template < class T >
void FIFOQueueClass < T >::print() const
{
  LinkedNodeClass < T >* tempPtr = head;
  cout << "Values in the queue include:" << endl;

  while (tempPtr != NULL)
  {
    cout << tempPtr->getValue() << " ";
    tempPtr = tempPtr->getNext();
  }
  // newline character printed at the end
  cout << endl;
}
