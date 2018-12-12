#pragma once

#include <GuiModel/GuiModelFwd.h>


class GuiCreator
{
public:

  static std::shared_ptr<GuiCollection> createGameGui();

private:
  GuiCreator() = default;
};
