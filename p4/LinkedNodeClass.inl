#include "LinkedNodeClass.h"
#include <cstdlib>


// custom ctor - creates LinkedNodeClass object with directions and value
template < class T >
LinkedNodeClass< T >::LinkedNodeClass(LinkedNodeClass<T> *inPrev,
                                 const T &inVal,
                                 LinkedNodeClass<T> *inNext)
{
  prevNode = inPrev;
  nodeVal = inVal;
  nextNode = inNext;
}


// getValue() - returns the value of the node
template < class T >
T LinkedNodeClass < T >::getValue() const
{
  return nodeVal;
}


// getNext() - returns the address of the next node
template < class T >
LinkedNodeClass < T >* LinkedNodeClass< T >::getNext() const
{
  return nextNode;
}


// getPrev() - returns the address of the previous node
template < class T >
LinkedNodeClass < T >* LinkedNodeClass< T >::getPrev() const
{
  return prevNode;
}


// setNextPointerToNull() - makes the next pointer point to NULL 
// instead of pointing to the current node
template < class T >
void LinkedNodeClass < T >::setNextPointerToNull()
{
  LinkedNodeClass* nodeFront;
  
  // have a pointer point to the next node
  nodeFront = getNext();

  // now that I can access the next node, make it point to NULL
  if (nodeFront != NULL)
  {
    nodeFront->prevNode = NULL;
  }

}


// setPreviousPointerToNull() - makes the previous pointer point to NULL
// instead of pointing to the current node
template < class T >
void LinkedNodeClass< T >::setPreviousPointerToNull()
{
  LinkedNodeClass* nodeBack;

  nodeBack = getPrev();
  if (nodeBack != NULL)
  {
    nodeBack->nextNode = NULL; 
  }
}


/*
setBeforeAndAfterPointers() - this function DOES NOT modify "this" node. 
Instead, it uses the pointers contained within this node to change the 
previous and next nodes so that they point to this node appropriately.
*/
template < class T>
void LinkedNodeClass< T >::setBeforeAndAfterPointers()
{
  LinkedNodeClass* nodeBack;
  LinkedNodeClass* nodeFront;
  nodeBack = getPrev();
  nodeFront = getNext();

  // if I'm not at the end of the list (ie a next node exists)
  if (nodeFront != NULL)
  {
    // make the next node point to me
    nodeFront->prevNode = this;
  }
  // if I'm not at the beginning of the list (ie a prev node exists)
  if (nodeBack != NULL)
  {
    // make the prev node point to me
    nodeBack->nextNode = this;
  }
}
