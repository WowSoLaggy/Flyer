#pragma once

#include <GuiModel/GuiModelFwd.h>


class GuiCreator
{
public:

  static std::shared_ptr<GuiCollection> create();

  static std::shared_ptr<HealthBar> createHealthBar();
  static std::shared_ptr<CurrentActionPanel> createCurrentActionPanel();

private:
  GuiCreator() = default;
};
