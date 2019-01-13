#pragma once

#include <Model/ModelFwd.h>
#include <Sdk/Vector.h>


class PhysicsController
{
public:
  PhysicsController() = delete;

  static void updateObjects(ObjectPtrs& io_objects, double i_dt);

private:
  static Vector3 getVirtualSpeed(ObjectPtr io_object, double i_dt);
  static Vector3 getRealSpeed(ObjectPtr io_object, double i_dt,
                              Vector3 i_virtualSpeed, const ObjectPtrs& io_objects);
  static void applySpeed(ObjectPtr io_object, double i_dt, Vector3 i_speed);
};
