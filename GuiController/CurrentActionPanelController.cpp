#include "stdafx.h"
#include "CurrentActionPanelController.h"

#include "GuiController.h"
#include "GuiCreator.h"
#include "GuiEvents.h"

#include <GuiModel/CurrentActionPanel.h>
#include <GuiModel/GuiCollection.h>
#include <Model/Creature.h>
#include <Model/IAction.h>
#include <Model/ObjectConverters.h>
#include <RenderApi/ICamera.h>


namespace
{

  std::string getTextureNameForAction(ActionType i_actionType)
  {
    static const std::string defaultTextureName = "ActionNone.dds";
    static const std::unordered_map<ActionType, std::string> actionTypeTextureMap = {
      { ActionType::Idle, "ActionIdle.dds" },
      { ActionType::MoveTo, "ActionMoveTo.dds" },
      { ActionType::Attack, "ActionAttack.dds" },
    };

    auto it = actionTypeTextureMap.find(i_actionType);
    if (it != actionTypeTextureMap.end())
      return it->second;

    return defaultTextureName;
  }

} // anonymous NS


CurrentActionPanelController::CurrentActionPanelController(GuiController& io_guiController, GuiCollection& io_guiCollection,
                                                           const ICamera& i_camera)
  : d_guiController(io_guiController)
  , d_guiCollection(io_guiCollection)
  , d_camera(i_camera)
{
}


IGuiPtr CurrentActionPanelController::getGuiForCreature(Sdk::UniqueId i_objectId)
{
  auto guiToObjectIt = std::find_if(d_currentActionPanelMap.begin(), d_currentActionPanelMap.end(),
                                    [&](const auto& pair) { return pair.second->getId() == i_objectId; });
  if (guiToObjectIt == d_currentActionPanelMap.end())
    return nullptr;

  auto& iGuiPtrs = d_guiCollection.guis;
  auto itGui = std::find_if(iGuiPtrs.begin(), iGuiPtrs.end(),
                            [&](const auto& i_gui) { return i_gui->getId() == guiToObjectIt->first; });
  if (itGui == iGuiPtrs.end())
    return nullptr;

  return *itGui;
}


void CurrentActionPanelController::update(CurrentActionPanel& io_currentActionPanel)
{
  auto creaturePtr = castObjectToCreature(d_currentActionPanelMap.at(io_currentActionPanel.getId()));
  positionCurrentActionPanel(io_currentActionPanel, creaturePtr);
}

IGuiPtr CurrentActionPanelController::updateActionTexture(ObjectPtr i_objectPtr)
{
  auto guiPtr = getGuiForCreature(i_objectPtr->getId());
  if (!guiPtr)
    return nullptr;

  auto actionType = i_objectPtr->getCurrentAction()->getActionType();
  auto textureName = getTextureNameForAction(actionType);

  auto& currentActionPanel = dynamic_cast<CurrentActionPanel&>(*guiPtr);
  currentActionPanel.setTextureName(textureName);

  return guiPtr;
}


void CurrentActionPanelController::addCurrentActionPanel(ObjectPtr i_objectPtr)
{
  auto pCurrentActionPanel = GuiCreator::createCurrentActionPanel();
  positionCurrentActionPanel(*pCurrentActionPanel, i_objectPtr);

  d_guiCollection.guis.push_back(pCurrentActionPanel);
  d_currentActionPanelMap[pCurrentActionPanel->getId()] = i_objectPtr;

  updateActionTexture(i_objectPtr);

  d_guiController.notify(GuiAddedEvent{ pCurrentActionPanel });
}

void CurrentActionPanelController::deleteCurrentActionPanel(Sdk::UniqueId i_objectId)
{
  auto guiToObjectIt = std::find_if(d_currentActionPanelMap.begin(), d_currentActionPanelMap.end(),
                                    [&](const auto& pair) { return pair.second->getId() == i_objectId; });
  if (guiToObjectIt == d_currentActionPanelMap.end())
    return;

  auto& iGuiPtrs = d_guiCollection.guis;
  auto itGui = std::find_if(iGuiPtrs.begin(), iGuiPtrs.end(),
                            [&](const auto& i_gui) { return i_gui->getId() == guiToObjectIt->first; });
  if (itGui == iGuiPtrs.end())
    return;

  d_guiController.notify(GuiDeletedEvent{ *itGui });

  iGuiPtrs.erase(itGui);
  d_currentActionPanelMap.erase(guiToObjectIt);
}

void CurrentActionPanelController::positionCurrentActionPanel(CurrentActionPanel& io_currentActionPanel)
{
  auto objectPtr = d_currentActionPanelMap.at(io_currentActionPanel.getId());
  if (objectPtr->isCreature())
    positionCurrentActionPanel(io_currentActionPanel, castObjectToCreature(objectPtr));
}

void CurrentActionPanelController::positionCurrentActionPanel(
  CurrentActionPanel& io_currentActionPanel, ObjectPtr i_objectPtr)
{
  auto pos = d_camera.worldToScreen(i_objectPtr->getPosition());
  io_currentActionPanel.setPosition(pos);
}
