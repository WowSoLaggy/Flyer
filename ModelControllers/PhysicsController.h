#pragma once

#include <Model/ModelFwd.h>


class PhysicsController
{
public:
  PhysicsController() = delete;

  static void updateObjects(std::vector<IRealObjectPtr>& io_objects, double i_dt);

private:
  static void updateObject(IRealObjectPtr io_object, double i_dt);
};
