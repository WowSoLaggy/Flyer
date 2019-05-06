#pragma once

#include <Model/ModelFwd.h>
#include <LaggySdk/Vector.h>


class PhysicsController
{
public:
  PhysicsController() = delete;

  static void updateObjects(ObjectPtrs& io_objects, double i_dt);

private:
  static Sdk::Vector3 getVirtualSpeed(ObjectPtr io_object, double i_dt);
  static Sdk::Vector3 getRealSpeed(ObjectPtr io_object, double i_dt,
                              const Sdk::Vector3& i_virtualSpeed, const ObjectPtrs& io_objects);
  static void applySpeed(ObjectPtr io_object, double i_dt, Sdk::Vector3 i_speed);
};
