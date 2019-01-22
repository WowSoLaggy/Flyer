#pragma once

#include <GuiModel/GuiModelFwd.h>


class HudCreator
{
public:
  static std::shared_ptr<HudCollection> createGameHud();

private:
  HudCreator() = default;
};
