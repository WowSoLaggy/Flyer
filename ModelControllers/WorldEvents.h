#pragma once

#include <Model/ModelFwd.h>
#include <Sdk/IEvent.h>


class ObjectAddedEvent : public IEvent
{
public:

  ObjectAddedEvent(ObjectPtr i_object)
    : d_object(i_object)
  {
  }

  ObjectPtr getObject() const { return d_object; }

private:

  ObjectPtr d_object;
};


class ObjectDeletedEvent : public IEvent
{
public:

  ObjectDeletedEvent(ObjectPtr i_object)
    : d_object(i_object)
  {
  }

  ObjectPtr getObject() const { return d_object; }

private:

  ObjectPtr d_object;
};

