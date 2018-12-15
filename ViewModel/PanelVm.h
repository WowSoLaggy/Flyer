#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>


class PanelVm : public GuiVm
{
public:

  PanelVm(const IResourceController& i_resourceController, const Panel& i_panel);

  virtual void render(IRenderer2d& i_renderer) const override;

  virtual const IGui& getGui() const override;

private:

  const Panel& d_panel;
  const ResourceId d_textureResourceId;

};
