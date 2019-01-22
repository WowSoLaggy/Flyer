#include "stdafx.h"
#include "GuiCollectionVm.h"

#include "CurrentActionPanelVm.h"
#include "HealthBarVm.h"
#include "LabelVm.h"
#include "PanelVm.h"

#include <GuiController/GuiController.h>
#include <GuiController/GuiEvents.h>
#include <GuiModel/CurrentActionPanel.h>
#include <GuiModel/GuiCollection.h>
#include <GuiModel/HealthBar.h>
#include <GuiModel/Label.h>
#include <GuiModel/Panel.h>
#include <RenderApi/IRenderer2d.h>


GuiCollectionVm::GuiCollectionVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
{
}


void GuiCollectionVm::buildFromCollection(IGuiController& i_guiController)
{
  auto& guiController = dynamic_cast<GuiController&>(i_guiController);

  for (const auto gui : guiController.getCollection().guis)
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
  else if (const auto* pGuiResourceChanged = dynamic_cast<const GuiResourcesChanged*>(&i_event))
    onGuiResourcesChanged(*pGuiResourceChanged->getGui());
}


void GuiCollectionVm::onGuiAdded(const IGui& i_gui)
{
  if (const auto* pLabel = dynamic_cast<const Label*>(&i_gui))
    d_guiVms.push_back(std::make_shared<LabelVm>(d_resourceController, *pLabel));
  else if (const auto* pPanel = dynamic_cast<const Panel*>(&i_gui))
    d_guiVms.push_back(std::make_shared<PanelVm>(d_resourceController, *pPanel));
  else if (const auto* pHealthBar = dynamic_cast<const HealthBar*>(&i_gui))
    d_guiVms.push_back(std::make_shared<HealthBarVm>(d_resourceController, *pHealthBar));
  else if (const auto* pCurrentActionPanel = dynamic_cast<const CurrentActionPanel*>(&i_gui))
    d_guiVms.push_back(std::make_shared<CurrentActionPanelVm>(d_resourceController, *pCurrentActionPanel));
}

void GuiCollectionVm::onGuiDeleted(const IGui& i_gui)
{
  d_guiVms.erase(std::remove_if(d_guiVms.begin(), d_guiVms.end(),
                                [&](std::shared_ptr<GuiVm> i_guiVm)
  {
    return i_guiVm->getGui().getId() == i_gui.getId();
  }), d_guiVms.end());
}

void GuiCollectionVm::onGuiResourcesChanged(const IGui& i_gui)
{
  auto it = std::find_if(d_guiVms.begin(), d_guiVms.end(),
                         [&](std::shared_ptr<GuiVm> i_guiVm) { return i_guiVm->getGui().getId() == i_gui.getId(); });
  if (it == d_guiVms.end())
    return;

  (*it)->reloadResources(d_resourceController);
}
