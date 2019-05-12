#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>


class CurrentActionPanelVm : public GuiVm
{
public:

  CurrentActionPanelVm(const Dx::IResourceController& i_resourceController,
                       const CurrentActionPanel& i_currentActionPanelVm);

  virtual void reloadResources(const Dx::IResourceController& i_resourceController) override;
  virtual void render(Dx::IRenderer& i_renderer) const override;

  virtual const IGui& getGui() const override;

private:

  const CurrentActionPanel& d_currentActionPanel;
  Dx::ResourceId d_textureResourceId;
};
