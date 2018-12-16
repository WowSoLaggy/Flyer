#pragma once

#include <GuiModel/GuiModelFwd.h>


class GuiCreator
{
public:

  static std::shared_ptr<GuiCollection> createGameGui();

  static std::shared_ptr<HealthBar> createHealthBar();

private:
  GuiCreator() = default;
};
