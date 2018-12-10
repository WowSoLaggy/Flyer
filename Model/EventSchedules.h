#pragma once

#include "IEventSchedule.h"


class EventSchedulePeriodic : public IEventSchedule
{
private:
  double d_period;
};
