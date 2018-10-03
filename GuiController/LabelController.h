#pragma once

#include <GuiModel/GuiModelFwd.h>


class LabelController
{
public:

  static void update(Label& io_label, double i_dt);

private:

  LabelController() = default;

};
