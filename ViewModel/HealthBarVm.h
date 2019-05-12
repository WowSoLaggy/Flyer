#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>


class HealthBarVm : public GuiVm
{
public:

  HealthBarVm(const Dx::IResourceController& i_resourceController, const HealthBar& i_healthBar);

  virtual void reloadResources(const Dx::IResourceController& i_resourceController) override;
  virtual void render(Dx::IRenderer& i_renderer) const override;

  virtual const IGui& getGui() const override;

private:

  const HealthBar& d_healthBar;
  Dx::ResourceId d_textureBackResourceId;
  Dx::ResourceId d_textureFrontResourceId;
};
