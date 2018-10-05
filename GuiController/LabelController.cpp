#include "stdafx.h"
#include "LabelController.h"

#include <GuiModel/Label.h>
#include <Sdk/StringUtils.h>


void LabelController::update(Label& io_label, double i_dt)
{
  std::string text;

  static double totalTime = 0;
  totalTime += i_dt;
  
  text += "Total time: " + std::to_string((int)totalTime) + "s";
  text += "\nFPS: " + std::to_string((int)(1.0 / i_dt));
  text += "\ndt: " + Utils::toString(i_dt, 2);

  io_label.setText(text);
}
