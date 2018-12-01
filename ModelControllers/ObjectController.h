#pragma once

#include <Model/ModelFwd.h>


class ObjectController
{
public:

  static void updateObject(Object& io_object, double i_dt, World& io_world);

private:
  ObjectController() = default;
};
