#pragma once

#include "ModelControllersFwd.h"

#include <Model/ModelFwd.h>


class ObjectController
{
public:

  static void updateObject(ObjectPtr& io_object, double i_dt, WorldController& io_worldController);

private:

  ObjectController() = default;

  static ObjectId d_destinationArrowId;

};
