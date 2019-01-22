#include "stdafx.h"
#include "CollisionShapeHudVm.h"

#include <GuiModel/CollisionShapeHud.h>
#include <RenderApi/IRenderer3d.h>
#include <RenderApi/IResourceController.h>


CollisionShapeHudVm::CollisionShapeHudVm(const IResourceController& i_resourceController,
                                          const CollisionShapeHud& i_collisionShapeHud)
  : d_collisionShapeHud(i_collisionShapeHud)
{
  reloadResources(i_resourceController);
}


void CollisionShapeHudVm::reloadResources(const IResourceController& i_resourceController)
{
  d_meshResourceId = i_resourceController.getResourceId(d_collisionShapeHud.getModelName());
  d_textureResourceId = i_resourceController.getResourceId(d_collisionShapeHud.getTextureName());
}

void CollisionShapeHudVm::render(IRenderer& i_renderer) const
{
  auto& renderer3d = dynamic_cast<IRenderer3d&>(i_renderer);
  renderer3d.renderObject(d_meshResourceId, d_textureResourceId, nullptr,
                          d_collisionShapeHud.getPosition(), d_collisionShapeHud.getRotation(), false);
}


const IGui& CollisionShapeHudVm::getGui() const
{
  return d_collisionShapeHud;
}
