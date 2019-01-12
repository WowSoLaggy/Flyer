#pragma once

#include <Model/ModelFwd.h>
#include <Sdk/Vector.h>


class PhysicsController
{
public:
  PhysicsController() = delete;

  static void updateObjects(std::vector<IRealObjectPtr>& io_objects, double i_dt);

private:
  static Vector3 getVirtualSpeed(IRealObjectPtr io_object, double i_dt);
  static void applySpeed(IRealObjectPtr io_object, double i_dt, Vector3 i_speed);
};
