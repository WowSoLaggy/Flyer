#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>


class CollisionShapeGui3dVm : public GuiVm
{
public:
  CollisionShapeGui3dVm(const Dx::IResourceController& i_resourceController,
                        const CollisionShapeGui3d& i_collisionShapeGui3d);

  virtual void reloadResources(const Dx::IResourceController& i_resourceController) override;
  virtual void render(Dx::IRenderer& i_renderer) const override;

  virtual const IGui& getGui() const override;

private:
  const CollisionShapeGui3d& d_collisionShapeGui3d;
  Dx::ResourceId d_meshResourceId;
  Dx::ResourceId d_textureResourceId;
};
