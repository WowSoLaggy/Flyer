#include "stdafx.h"
#include "PanelVm.h"

#include <GuiModel/Panel.h>
#include <RenderApi/IRenderer2d.h>
#include <RenderApi/IResourceController.h>


PanelVm::PanelVm(const IResourceController& i_resourceController, const Panel& i_panel)
  : d_panel(i_panel)
{
  reloadResources(i_resourceController);
}


void PanelVm::reloadResources(const IResourceController& i_resourceController)
{
  d_textureResourceId = i_resourceController.getResourceId(d_panel.getTextureName());
}

void PanelVm::render(IRenderer& i_renderer) const
{
  auto& renderer2d = dynamic_cast<IRenderer2d&>(i_renderer);
  renderer2d.renderTexture(d_textureResourceId, d_panel.getPosition());
}


const IGui& PanelVm::getGui() const
{
  return d_panel;
}
