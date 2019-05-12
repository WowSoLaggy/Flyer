#include "stdafx.h"
#include "CurrentActionPanelVm.h"

#include <GuiModel/CurrentActionPanel.h>
#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>


CurrentActionPanelVm::CurrentActionPanelVm(const Dx::IResourceController& i_resourceController,
                                           const CurrentActionPanel& i_currentActionPanel)
  : d_currentActionPanel(i_currentActionPanel)
{
  reloadResources(i_resourceController);
}


void CurrentActionPanelVm::reloadResources(const Dx::IResourceController& i_resourceController)
{
  d_textureResourceId = i_resourceController.getResourceId(d_currentActionPanel.getTextureName());
}

void CurrentActionPanelVm::render(Dx::IRenderer& i_renderer) const
{
  auto& renderer2d = dynamic_cast<Dx::IRenderer2d&>(i_renderer);
  renderer2d.renderTexture(d_textureResourceId, d_currentActionPanel.getPosition(), d_currentActionPanel.getSize());
}


const IGui& CurrentActionPanelVm::getGui() const
{
  return d_currentActionPanel;
}
