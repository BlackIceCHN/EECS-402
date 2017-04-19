#ifndef _TEMPLATE_SORTED_LIST_CLASS_
#define _TEMPLATE_SORTED_LIST_CLASS_

#include "LinkedNodeClass.h"
template < class T >

//The sorted list class does not store any data directly. Instead,
//it contains a collection of LinkedNodeClass objects, each of which
//contains one element.


class SortedListClass
{
private:
  // points to first node in a list. NULL if list is empty
  LinkedNodeClass< T > *head;
  // points to last node in a list. NULL if list is empty
  LinkedNodeClass< T > *tail;

public:
  // default ctor. Initialize list to be an empty list
  SortedListClass();

  //Copy ctor, will make copy of list
  SortedListClass(const SortedListClass< T > &rhs);

  // clears list to empty state without any memory leaks
  void clear();

  // allows user to insert a val into list. Will insert it in teh appropriate
  // location based on value being inserted. If node val is equal to a node[s] 
  // in the list, place the newly inserted list AFTER the original one[s]

  void insertValue(const T &valToInsert); // the val to insert in list

  // prints contents of list from head to tail
  void printForward() const;

  // prints contents of list from tail to head
  void printBackward() const;

  // removes front item from list and returns value contained in it 
  // via the reference parameter. If list was empty, return false
  // if list not empty and front item removed, return true and reference
  // paramter will be set to the removed item

  bool removeFront(T &theVal);

  // same thing as above for for last item

  bool removeLast(T &theVal);

  // returns number of nodes contained in list
  int getNumElems() const;

  // provides value stored in the node at the index provided
  // if out of range, outVal is unchanged and return false
  // otherwise, return true and outVal will contain a copy of the value
  // at that location

  bool getElemAtIndex(const int index, T &outVal) const;
};




#include "SortedListClass.inl"
#endif