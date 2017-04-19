#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include <iostream>
#include <cstdlib>

/* HEADER - The implementation of SortedListClass. A more thorough 
explanation of what SLC does can be found in the .h file
*/


// default ctor - creates empty SortedListClass object
template < class T >
SortedListClass < T >::SortedListClass()
{
  head = NULL;
  tail = NULL;
}

// copy constructor - makes a copy of a of the list such that changing one 
// wont affect the other
template < class T >
SortedListClass < T >::SortedListClass(const SortedListClass < T > &rhs)
{
  int value;
  // get size of the list to copy
  int rhsLength = rhs.getNumElems();
  T returnVal;
  head = NULL;
  tail = NULL;


  for (int i = 0; i < rhsLength; i++)
  {
    rhs.getElemAtIndex(i, returnVal);
    insertValue(returnVal);
  }
}


// Allows the user to insert a value into the list. It will insert in the 
// correct location based on the value being inserted. If the node value
// being inserted is found to be "equal to" one or more node values
// already in the list, the newly inserted node will be placed AFTER
// the previously inserted nodes.
template < class T >
void SortedListClass < T >::insertValue(const T &valToInsert)
{
  bool positionFound = false;
  //T compare;
  int iter = 0;
  int firstStep = 1;
  LinkedNodeClass < T >* newNode;

  if (tail == NULL) // if list is empty
  {
    // make new node
    newNode = new LinkedNodeClass< T >(NULL, valToInsert, NULL);
    // have head and tail point to it
    head = newNode;
    tail = newNode;
    positionFound = true;
    //cout << "value of added node is: " << newNode->getValue() << endl;

  }
  LinkedNodeClass < T >* tempPtr = head;

  if (!positionFound)
  {
    do
    {
      iter+= 1;
      //cout << "temp has address: " << temp << endl;
      //cout << "val to insert is: " << valToInsert << endl;

      // get value of current node
      T compare = tempPtr->getValue();
      //cout << "compare: " << compare << endl;

      // lets us know if we should keep searching through SL 
      if (!(compare <= valToInsert))
      {
        //cout << "in if statement" << endl;
        positionFound = true;
        newNode = new LinkedNodeClass< T >(tempPtr->getPrev(),
                                      valToInsert,
                                      tempPtr);
        // if the new node is smaller than all other nodes
        if (iter == firstStep)
        {
          //cout << "New first node!" << endl;
          head = newNode;
          
        }
        newNode->setBeforeAndAfterPointers();
      }
      // if we're at the last node
      else if (tempPtr->getNext() == NULL)
      {
        //cout << "We're at the last node" << endl;
        positionFound = true;

        // get a new last node
        newNode = new LinkedNodeClass< T >(tempPtr, valToInsert, NULL);
        tail = newNode; 
        newNode->setBeforeAndAfterPointers(); 

      }
      else // if we're not at the end
      {
        //cout << "in else statement" << endl;
        tempPtr = tempPtr->getNext(); 
        //cout << "getNext works" << endl;
        //cout << "new address of temp: " << temp << endl;
      }
    } while (!positionFound);
  }
}


// Clears the list to an empty state without resulting in any
// memory leaks.
template < class T >
void SortedListClass < T >::clear()
{
  // point to first node to be deleted
  //LinkedNodeClass < T >* tempPtr = head;
  int max = getNumElems();
  int i;
  T node;
  for (i = 0; i < max; i++)
  {
    //cout << "removing node " << i << endl;
    removeFront(node);
  }
  // reset head and tail
  head = NULL;
  tail = NULL;
}


// getNumElems() returns number of nodes contained in the list
template < class T >
int SortedListClass < T >::getNumElems() const
{
  int numElems = 0;
  LinkedNodeClass < T >* tempPtr = head;
  
  while (tempPtr != NULL)
  {
    numElems += 1;
    tempPtr = tempPtr->getNext();
  }

  return numElems;
}


// Removes the front item from the list and returns the value that
// was contained in it via the reference parameter. If the list
// was empty, the function returns false to indicate failure, and
// the contents of the reference parameter upon return is undefined.
// If the list was not empty and the first item was successfully
// removed, true is returned, and the reference parameter will
// be set to the item that was removed.
template < class T >
bool SortedListClass < T >::removeFront(T &theVal)
{
  bool success = true;
  LinkedNodeClass < T >* tempPtr;

  if (tail == NULL)
  {
    cout << "List is empty. Can't delete." << endl;
    success = false;
  }
  else
  {
    tempPtr = head;
    // make sure the new first node points to null
    tempPtr->setNextPointerToNull();
    theVal = tempPtr->getValue();

    // if it's the first node set both head to tail
    if (tempPtr->getNext() == NULL)
    {
      head = tempPtr->getNext();
      tail = tempPtr->getPrev();
    }
    else // else, just set head to null
    {
      head = tempPtr->getNext();
    }
    // free memory
    delete tempPtr;
    //cout << "value: " << theVal << endl;
  }
  return success;
}


// Removes the last item from the list and returns the value that
// was contained in it via the reference parameter. If the list
// was empty, the function returns false to indicate failure, and
// the contents of the reference parameter upon return is undefined.
// If the list was not empty and the last item was successfully
// removed, true is returned, and the reference parameter will
// be set to the item that was removed.
template < class T >
bool SortedListClass < T >::removeLast(T &theVal)
{
  bool success = true;
  LinkedNodeClass < T >* tempPtr;

  if (tail == NULL)
  {
    cout << "List is empty. Can't delete." << endl;
    success = false;
  }
  else
  {
    tempPtr = tail;
    // make sure the new last node points to NULL
    tempPtr->setPreviousPointerToNull();
    theVal = tempPtr->getValue();
    // if it's the first node
    if (tempPtr->getPrev() == NULL)
    {
      tail = tempPtr->getPrev();
      head = tempPtr->getNext();
    }
    else
    {
      tail = tempPtr->getPrev();
    }
    // free memory
    delete tempPtr;
    //cout << "value: " << theVal << endl;
  }
  return success;
}


// Prints the contents of the list from head to tail to the screen.
// Begins with a line reading "Forward List Contents Follow:", then
// prints one list element per line, indented two spaces, then prints
// the line "End Of List Contents" to indicate the end of the list
template < class T >
void SortedListClass < T >::printForward() const
{
  LinkedNodeClass < T >* tempPtr = head;


  cout << "Forward List Content Follow:" << endl;
  while (tempPtr != NULL)
  {
    // print the current node's value the move to the next node
    cout << tempPtr->getValue() << endl;
    tempPtr = tempPtr->getNext();
  }
  cout << "  " << "End of List Contents" << endl;
}


// Begins with a line reading "Backward List Contents Follow:", then
// prints one list element per line, indented two spaces, then prints
// the line "End Of List Contents" to indicate the end of the list
template < class T >
void SortedListClass < T >::printBackward() const
{
  LinkedNodeClass < T >* tempPtr = tail;

  cout << "Backward List Content Follow:" << endl;
  while (tempPtr != NULL) // this is equivalent to (!temp)
  {
    cout << tempPtr->getValue() << endl;
    tempPtr = tempPtr->getPrev();
  }
  cout << "  " << "End of List Contents" << endl;
}


// Provides the value stored in the node at index provided in the
// "index" parameter. If the index is out of range, then outVal
// remains unchanged and false is returned. Otherwise, the function
// returns true, and the reference parameter outVal will contain
// a copy of the value at that location.
template < class T >
bool SortedListClass < T >::getElemAtIndex(const int index,
                                           T &outVal) const
{
  int numElems = getNumElems();
  bool success = true;
  LinkedNodeClass < T >* tempPtr = head;

  // if you're asking outside the range
  if (index > numElems)
  {
    success = false;
  }
  else
  {
    // go to the index
    for (int i = 0; i < index; i++)
    {
      tempPtr = tempPtr->getNext();
    }
  }
  // get the element at that index
  outVal = tempPtr->getValue();
  //cout << "value at index " << index << " is " << outVal << endl;
  return success;  
}

