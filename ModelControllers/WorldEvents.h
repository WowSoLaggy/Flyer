#pragma once

#include <Model/ModelFwd.h>
#include <Sdk/IEvent.h>


class ObjectAddedEvent : public IEvent
{
public:

  ObjectAddedEvent(const Object& i_object)
    : d_object(i_object)
  {
  }

  const Object& getObject() const { return d_object; }

private:

  const Object& d_object;
};


class ObjectDeletedEvent : public IEvent
{
public:

  ObjectDeletedEvent(const Object& i_object)
    : d_object(i_object)
  {
  }

  const Object& getObject() const { return d_object; }

private:

  const Object& d_object;
};

