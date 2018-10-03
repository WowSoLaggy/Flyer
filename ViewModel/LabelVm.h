#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>
#include <RenderApi/RenderApiFwd.h>


class LabelVm : public GuiVm
{
public:

  LabelVm(const IResourceController& i_resourceController, const Label& i_label);

  virtual ResourceId getFontResourceId() const override { return d_fontResourceId; }

private:

  const Label& d_label;
  const ResourceId d_fontResourceId;

};
