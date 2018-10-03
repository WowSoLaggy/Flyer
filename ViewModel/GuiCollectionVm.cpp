#include "stdafx.h"
#include "GuiCollectionVm.h"

#include "LabelVm.h"

#include <GuiModel/GuiCollection.h>
#include <GuiModel/Label.h>
#include <RenderApi/IRenderer2d.h>


GuiCollectionVm::GuiCollectionVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
{
  d_renderer = IRenderer2d::create(io_renderDevice, i_resourceController);
}


void GuiCollectionVm::buildFromCollection(const GuiCollection& i_guiCollection)
{
  for (const auto gui : i_guiCollection.getGuis())
  {
    if (const auto* pLabel = dynamic_cast<const Label*>(gui.get()))
      d_guiVms.push_back(std::make_shared<LabelVm>(d_resourceController, *pLabel));
  }
}


void GuiCollectionVm::render() const
{
  d_renderer->beginScene();

  for (const auto& guiVm : d_guiVms)
    d_renderer->renderObject(*guiVm);

  d_renderer->endScene();
}
