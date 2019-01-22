#pragma once

#include <GuiModel/GuiModelFwd.h>


class HudCreator
{
public:
  static std::shared_ptr<HudCollection> createGameHud();

  static std::shared_ptr<CollisionShapeHud> createCollisionShapeHud();

private:
  HudCreator() = default;
};
