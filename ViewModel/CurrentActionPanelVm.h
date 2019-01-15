#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>


class CurrentActionPanelVm : public GuiVm
{
public:

  CurrentActionPanelVm(const IResourceController& i_resourceController,
                       const CurrentActionPanel& i_currentActionPanelVm);

  virtual void reloadResources(const IResourceController& i_resourceController) override;
  virtual void render(IRenderer2d& i_renderer) const override;

  virtual const IGui& getGui() const override;

private:

  const CurrentActionPanel& d_currentActionPanel;
  ResourceId d_textureResourceId;
};
