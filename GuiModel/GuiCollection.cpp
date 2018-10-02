#include "stdafx.h"
#include "GuiCollection.h"


void GuiCollection::addGui(std::shared_ptr<IGui> i_gui)
{
  d_guis.push_back(i_gui);
}
