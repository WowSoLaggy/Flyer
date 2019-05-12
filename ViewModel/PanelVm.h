#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>


class PanelVm : public GuiVm
{
public:

  PanelVm(const Dx::IResourceController& i_resourceController, const Panel& i_panel);

  virtual void reloadResources(const Dx::IResourceController& i_resourceController) override;
  virtual void render(Dx::IRenderer& i_renderer) const override;

  virtual const IGui& getGui() const override;

private:

  const Panel& d_panel;
  Dx::ResourceId d_textureResourceId;

};
