#include "stdafx.h"
#include "CurrentActionPanelVm.h"

#include <GuiModel/CurrentActionPanel.h>
#include <RenderApi/IRenderer2d.h>
#include <RenderApi/IResourceController.h>


CurrentActionPanelVm::CurrentActionPanelVm(const IResourceController& i_resourceController,
                                           const CurrentActionPanel& i_currentActionPanel)
  : d_currentActionPanel(i_currentActionPanel)
{
  reloadResources(i_resourceController);
}


void CurrentActionPanelVm::reloadResources(const IResourceController& i_resourceController)
{
  d_textureResourceId = i_resourceController.getResourceId(d_currentActionPanel.getTextureName());
}

void CurrentActionPanelVm::render(IRenderer2d& i_renderer) const
{
  i_renderer.renderTexture(d_textureResourceId, d_currentActionPanel.getPosition(), d_currentActionPanel.getSize());
}


const IGui& CurrentActionPanelVm::getGui() const
{
  return d_currentActionPanel;
}
