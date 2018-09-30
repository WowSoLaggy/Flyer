#pragma once

#include <Model/ModelFwd.h>


class ObjectController
{
public:

  static void updateObject(Object& i_object, double i_dt);

private:
  ObjectController() = default;
};
