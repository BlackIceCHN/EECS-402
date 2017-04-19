#ifndef _EVENT_TYPE_CLASS_
#define _EVENT_TYPE_CLASS_

/* This class is used to 'label' and distinguish the different types
of events that go into our sorted list. That way, when we handle the 
next event, we know whether it's a rider arriving or a car arriving
It has private data members:
  eventType - distinguishes the type of event
  value - value of the event
*/

class EventTypeClass
{
public:
  EventTypeClass();
  EventTypeClass(int type, const int &inVal);
  bool operator<=(const EventTypeClass &rhs);
  int getEventType();


private:
  int eventType;
  int value;
};



//#include "EventTypeClass.inl"
#endif