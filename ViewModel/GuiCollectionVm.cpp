#include "stdafx.h"
#include "GuiCollectionVm.h"

#include "CollisionShapeGui3dVm.h"
#include "CurrentActionPanelVm.h"
#include "HealthBarVm.h"
#include "LabelVm.h"
#include "PanelVm.h"

#include <GuiController/GuiController.h>
#include <GuiController/GuiEvents.h>
#include <GuiModel/CollisionShapeGui3d.h>
#include <GuiModel/CurrentActionPanel.h>
#include <GuiModel/GuiCollection.h>
#include <GuiModel/HealthBar.h>
#include <GuiModel/Gui3dCollection.h>
#include <GuiModel/Label.h>
#include <GuiModel/Panel.h>
#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IRenderer3d.h>


GuiCollectionVm::GuiCollectionVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
{
}


void GuiCollectionVm::buildFromCollection(IGuiController& i_guiController)
{
  auto& guiController = dynamic_cast<GuiController&>(i_guiController);

  for (const auto gui3d : guiController.getGui3dCollection().guis)
    onGuiAdded(*gui3d);
  for (const auto gui : guiController.getGuiCollection().guis)
    onGuiAdded(*gui);

  connectTo(guiController);
}


void GuiCollectionVm::render(IRenderer2d& i_renderer2d, IRenderer3d& i_renderer3d, double i_dt) const
{
  for (const auto& gui3dVm : d_guis3d)
    gui3dVm->render(i_renderer3d);
  for (const auto& guiVm : d_guis)
    guiVm->render(i_renderer2d);
}


void GuiCollectionVm::processEvent(const Sdk::IEvent& i_event)
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
  if (i_gui.is3d())
  {
    if (const auto* pCollisionShapeGui3d = dynamic_cast<const CollisionShapeGui3d*>(&i_gui))
      d_guis3d.push_back(std::make_shared<CollisionShapeGui3dVm>(d_resourceController, *pCollisionShapeGui3d));
  }
  else
  {
    if (const auto* pLabel = dynamic_cast<const Label*>(&i_gui))
      d_guis.push_back(std::make_shared<LabelVm>(d_resourceController, *pLabel));
    else if (const auto* pPanel = dynamic_cast<const Panel*>(&i_gui))
      d_guis.push_back(std::make_shared<PanelVm>(d_resourceController, *pPanel));
    else if (const auto* pHealthBar = dynamic_cast<const HealthBar*>(&i_gui))
      d_guis.push_back(std::make_shared<HealthBarVm>(d_resourceController, *pHealthBar));
    else if (const auto* pCurrentActionPanel = dynamic_cast<const CurrentActionPanel*>(&i_gui))
      d_guis.push_back(std::make_shared<CurrentActionPanelVm>(d_resourceController, *pCurrentActionPanel));
  }
}

void GuiCollectionVm::onGuiDeleted(const IGui& i_gui)
{
  auto& collection = i_gui.is3d() ? d_guis3d : d_guis;

  collection.erase(std::remove_if(collection.begin(), collection.end(),
                                  [&](std::shared_ptr<GuiVm> i_guiVm)
  {
    return i_guiVm->getGui().getId() == i_gui.getId();
  }), collection.end());
}

void GuiCollectionVm::onGuiResourcesChanged(const IGui& i_gui)
{
  auto& collection = i_gui.is3d() ? d_guis3d : d_guis;

  auto it = std::find_if(collection.begin(), collection.end(),
                         [&](std::shared_ptr<GuiVm> i_guiVm) { return i_guiVm->getGui().getId() == i_gui.getId(); });
  if (it == collection.end())
    return;

  (*it)->reloadResources(d_resourceController);
}
