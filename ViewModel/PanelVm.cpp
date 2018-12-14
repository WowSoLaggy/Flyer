#include "stdafx.h"
#include "PanelVm.h"

#include <GuiModel/Panel.h>
#include <RenderApi/IResourceController.h>


PanelVm::PanelVm(const IResourceController& i_resourceController, const Panel& i_panel)
  : d_panel(i_panel)
  , d_textureResourceId(i_resourceController.getResourceId(i_panel.getTextureName()))
{
}
