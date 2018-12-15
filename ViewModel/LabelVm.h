#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>


class LabelVm : public GuiVm
{
public:

  LabelVm(const IResourceController& i_resourceController, const Label& i_label);

  virtual void render(IRenderer2d& i_renderer) const override;

  virtual const IGui& getGui() const override;

private:

  const Label& d_label;
  const ResourceId d_fontResourceId;

};
