#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>


class HealthBarVm : public GuiVm
{
public:

  HealthBarVm(const IResourceController& i_resourceController, const HealthBar& i_healthBar);

  virtual void render(IRenderer2d& i_renderer) const override;

  virtual const IGui& getGui() const override;

private:

  const HealthBar& d_healthBar;
  const ResourceId d_textureBackResourceId;
  const ResourceId d_textureFrontResourceId;
};
