#include "stdafx.h"
#include "CollisionShapeGui3dVm.h"

#include <GuiModel/CollisionShapeGui3d.h>
#include <RenderApi/IRenderer3d.h>
#include <RenderApi/IResourceController.h>


CollisionShapeGui3dVm::CollisionShapeGui3dVm(const IResourceController& i_resourceController,
                                             const CollisionShapeGui3d& i_collisionShapeGui3d)
  : d_collisionShapeGui3d(i_collisionShapeGui3d)
{
  reloadResources(i_resourceController);
}


void CollisionShapeGui3dVm::reloadResources(const IResourceController& i_resourceController)
{
  d_meshResourceId = i_resourceController.getResourceId(d_collisionShapeGui3d.getModelName());
  d_textureResourceId = i_resourceController.getResourceId(d_collisionShapeGui3d.getTextureName());
}

void CollisionShapeGui3dVm::render(IRenderer& i_renderer) const
{
  auto& renderer3d = dynamic_cast<IRenderer3d&>(i_renderer);
  renderer3d.renderObject(d_meshResourceId, d_textureResourceId, nullptr,
                          d_collisionShapeGui3d.getPosition(), d_collisionShapeGui3d.getRotation(), false);
}


const IGui& CollisionShapeGui3dVm::getGui() const
{
  return d_collisionShapeGui3d;
}
