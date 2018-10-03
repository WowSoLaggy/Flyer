#include "stdafx.h"
#include "LabelController.h"

#include <GuiModel/Label.h>


void LabelController::update(Label& io_label, double i_dt)
{
  std::string text;

  static double totalTime = 0;
  totalTime += i_dt;
  
  text += "dt: " + std::to_string(i_dt);
  text += "\nFPS: " + std::to_string(1.0 / i_dt);
  text += "\nTotal time: " + std::to_string(totalTime);

  io_label.setText(text);
}
