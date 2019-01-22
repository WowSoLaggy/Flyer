#pragma once

#include "GuiVm.h"

#include <GuiModel/GuiModelFwd.h>


class CollisionShapeHudVm : public GuiVm
{
public:
  CollisionShapeHudVm(const IResourceController& i_resourceController,
                      const CollisionShapeHud& i_collisionShapeHud);

  virtual void reloadResources(const IResourceController& i_resourceController) override;
  virtual void render(IRenderer& i_renderer) const override;

  virtual const IGui& getGui() const override;

private:
  const CollisionShapeHud& d_collisionShapeHud;
  ResourceId d_meshResourceId;
  ResourceId d_textureResourceId;
};
