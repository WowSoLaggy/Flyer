#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>
#include <RenderApi/RenderApiFwd.h>


class PanelVm : public GuiVm
{
public:

  PanelVm(const IResourceController& i_resourceController, const Panel& i_panel);

  ResourceId getTextureResourceId() const { return d_textureResourceId; }

private:

  const Panel& d_panel;
  const ResourceId d_textureResourceId;

};
