#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>


class HealthBarVm : public GuiVm
{
public:

  HealthBarVm(const IResourceController& i_resourceController, const HealthBar& i_healthBar);

  virtual void reloadResources(const IResourceController& i_resourceController) override;
  virtual void render(IRenderer& i_renderer) const override;

  virtual const IGui& getGui() const override;

private:

  const HealthBar& d_healthBar;
  ResourceId d_textureBackResourceId;
  ResourceId d_textureFrontResourceId;
};
