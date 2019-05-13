#pragma once

#include <LaggyDx/LaggyDxFwd.h>
#include <Model/ModelFwd.h>


class IWorldController
{
public:

  static std::shared_ptr<IWorldController> create(World& io_world);

public:

  virtual ~IWorldController() = default;

  virtual void update(double i_dt) = 0;
  virtual void processInput(const Dx::KeyboardState& i_keyboardState) = 0;
};
