#pragma once

#include "ViewModelFwd.h"

#include <GuiModel/GuiModelFwd.h>
#include <RenderApi/RenderApiFwd.h>


class GuiCollectionVm
{
public:

  GuiCollectionVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController);

  void buildFromCollection(const GuiCollection& i_guiCollection);

  void render() const;

private:

  IRenderDevice & d_renderDevice;
  const IResourceController& d_resourceController;

  std::shared_ptr<IRenderer2d> d_renderer;

  std::vector<std::shared_ptr<GuiVm>> d_guiVms;

};
