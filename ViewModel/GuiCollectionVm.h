#pragma once

#include "ViewModelFwd.h"

#include <GuiModel/GuiModelFwd.h>
#include <RenderApi/RenderApiFwd.h>


class GuiCollectionVm
{
public:

  GuiCollectionVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController);

  void buildFromCollection(const GuiCollection& i_guiCollection);

private:

  IRenderDevice & d_renderDevice;
  const IResourceController& d_resourceController;

  std::vector<std::shared_ptr<GuiVm>> d_guiVms;

};
