#ifndef _TEMPLATE_LINKED_NODE_CLASS_H_
#define _TEMPLATE_LINKED_NODE_CLASS_H_
template < class T >
class LinkedNodeClass
{
private:
  LinkedNodeClass *prevNode; // points the node behind current/this node
  T nodeVal; // value contained in node
  LinkedNodeClass *nextNode; // points to node after current/this node

public:
  // custom ctor - creates a node, assigns where it points to and who points to it
  LinkedNodeClass(LinkedNodeClass *inPrev, const T &inVal,
                  LinkedNodeClass *inNext);

  // returns value of type T that's stored in this node
  T getValue() const;

  // returns address of the node that this one points to
  LinkedNodeClass* getNext() const;

  // returns address of teh node that points to this one
  LinkedNodeClass* getPrev() const;


  // makes the next node point to null
  void setNextPointerToNull();

  // makes previous node point to null
  void setPreviousPointerToNull();

  // not sure how this works yet
   void setBeforeAndAfterPointers();
};




#include "LinkedNodeClass.inl"
#endif