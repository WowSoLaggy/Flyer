#include "stdafx.h"
#include "IGui.h"


GuiId IGui::s_nextId = 0;


IGui::IGui()
  : d_id(s_nextId++)
{
}
