#include "stdafx.h"
#include "GuiCollectionVm.h"

#include "LabelVm.h"
#include "PanelVm.h"

#include <GuiController/GuiController.h>
#include <GuiController/GuiEvents.h>
#include <GuiModel/GuiCollection.h>
#include <GuiModel/Label.h>
#include <GuiModel/Panel.h>


GuiCollectionVm::GuiCollectionVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
{
}


void GuiCollectionVm::buildFromCollection(IGuiController& i_guiController)
{
  auto& guiController = dynamic_cast<GuiController&>(i_guiController);

  for (const auto gui : guiController.getCollection().getGuis())
    onGuiAdded(*gui);

  connectTo(guiController);
}


void GuiCollectionVm::render(IRenderer2d& i_renderer, double i_dt) const
{
  for (const auto& guiVm : d_guiVms)
    guiVm->render(i_renderer);
}


void GuiCollectionVm::processEvent(const IEvent& i_event)
{
  if (const auto* pObjectAddedEvent = dynamic_cast<const GuiAddedEvent*>(&i_event))
    onGuiAdded(*pObjectAddedEvent->getGui());
  else if (const auto* pObjectDeletedEvent = dynamic_cast<const GuiDeletedEvent*>(&i_event))
    onGuiDeleted(*pObjectDeletedEvent->getGui());
}


void GuiCollectionVm::onGuiAdded(const IGui& i_gui)
{
  if (const auto* pLabel = dynamic_cast<const Label*>(&i_gui))
    d_guiVms.push_back(std::make_shared<LabelVm>(d_resourceController, *pLabel));
  else if (const auto* pPanel = dynamic_cast<const Panel*>(&i_gui))
    d_guiVms.push_back(std::make_shared<PanelVm>(d_resourceController, *pPanel));
}

void GuiCollectionVm::onGuiDeleted(const IGui& i_gui)
{
  d_guiVms.erase(std::remove_if(d_guiVms.begin(), d_guiVms.end(),
                                [&](std::shared_ptr<GuiVm> i_guiVm)
  {
    return i_guiVm->getGui().getId() == i_gui.getId();
  }), d_guiVms.end());
}
