#pragma once

#include "Callbacks.h"


class Engine
{
public:

  void run(ControlCallback i_controlCallback, UpdateCallback i_updateCallback);

};
