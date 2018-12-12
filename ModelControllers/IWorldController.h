#pragma once

#include <Model/ModelFwd.h>


class IWorldController
{
public:

  static std::shared_ptr<IWorldController> create(World& io_world);

public:

  virtual ~IWorldController() = default;

  virtual void update(double i_dt) = 0;
};
