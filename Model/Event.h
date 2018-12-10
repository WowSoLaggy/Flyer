#pragma once

#include "IEventSchedule.h"


using EventAction = std::function<void()>;


class Event
{
private:
  std::shared_ptr<IEventSchedule> d_eventSchedule;
  EventAction d_eventAction;
};
