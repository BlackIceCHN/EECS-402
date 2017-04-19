#include "EventTypeClass.h"

/* HEADER: Implementation of EventTypeClass. An in-depth description
can be found in the .h file */


// default ctor so that I can insert it in functions that require
// an object of class T
EventTypeClass::EventTypeClass()
{
  eventType = -1; // NOTHING
  value = -1; // NOTHING
}

// custom ctor - set's the type of an event and alue associated with it
EventTypeClass::EventTypeClass(int type, const int &inVal)
{
  eventType = type;
  value = inVal;
}


// getEventType() - returns the integer associated with a certain event
int EventTypeClass::getEventType()
{
  return eventType;
}


// operator<=(const EventTypeClass rhs) - this overloads the 
// greater than or equal to operator for objects of type EventTypeClass
bool EventTypeClass::operator<=(const EventTypeClass &rhs)
{
  bool success = false;
  if (value <= rhs.value)
  {
    success = true;
  }

  return success;
}

