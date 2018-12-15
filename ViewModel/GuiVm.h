#pragma once

#include <GuiModel/GuiModelFwd.h>
#include <RenderApi/RenderApiFwd.h>


class GuiVm
{
public:

  virtual ~GuiVm() = default;

  virtual void render(IRenderer2d& i_renderer) const = 0;

  virtual const IGui& getGui() const = 0;
};
