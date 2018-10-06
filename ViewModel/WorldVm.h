#pragma once

#include "ViewModelFwd.h"

#include <Model/ModelFwd.h>
#include <RenderApi/RenderApiFwd.h>


class WorldVm
{
public:

  WorldVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController);

  void buildFromWorld(const World& i_world);

  void render(IRenderer3d& i_renderer) const;

private:

  IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;

  std::shared_ptr<TerrainVm> d_terrainVm;
  std::vector<std::shared_ptr<ObjectVm>> d_objectVms;

};
