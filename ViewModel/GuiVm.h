#pragma once

#include <GuiModel/GuiModelFwd.h>
#include <LaggyDx/LaggyDxFwd.h>


class GuiVm
{
public:

  virtual ~GuiVm() = default;

  virtual void reloadResources(const Dx::IResourceController& i_resourceController) = 0;
  virtual void render(Dx::IRenderer& i_renderer) const = 0;

  virtual const IGui& getGui() const = 0;
};
