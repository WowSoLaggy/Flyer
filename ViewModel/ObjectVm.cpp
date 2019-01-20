#include "stdafx.h"
#include "ObjectVm.h"

#include <Model/IAction.h>
#include <Model/Object.h>
#include <RenderApi/IAnimationController.h>
#include <RenderApi/IRenderer3d.h>
#include <RenderApi/IResourceController.h>
#include <Sdk/Vector.h>


namespace
{

  static const std::unordered_map<ActionType, std::wstring> actionTypeStringsMap = {
    { ActionType::Idle, L"Idle" },
    { ActionType::MoveTo, L"Move" },
    { ActionType::Attack, L"Attack" },
  };

} // anonymous NS


ObjectVm::ObjectVm(const IResourceController& i_resourceController, const Object& i_object)
  : d_object(i_object)
  , d_meshResourceCmoId(i_resourceController.getResourceId(d_object.getModelName()))
{
  const auto& customTextureName = d_object.getCustomTextureName();
  d_customTextureId = customTextureName.empty() ?
    ResourceIdEmpty : i_resourceController.getResourceId(customTextureName);

  d_animationController = IAnimationController::getAnimationController(i_resourceController, d_meshResourceCmoId);
}


void ObjectVm::update(double i_dt)
{
  const auto objectActionType = d_object.getCurrentAction()->getActionType();
  const auto& objectActionName = actionTypeStringsMap.at(objectActionType);

  const auto& currentActionName = d_animationController->getCurrentAnimationName();

  if (objectActionName == currentActionName)
    d_animationController->update(i_dt);
  else
    d_animationController->setAnimation(objectActionName);
}

void ObjectVm::render(IRenderer3d& i_renderer) const
{
  if (!d_object.getVisibility())
    return;

  i_renderer.renderObject(d_meshResourceCmoId, d_customTextureId, *d_animationController,
    d_object.getPosition(), d_object.getRotation(), true);
}
