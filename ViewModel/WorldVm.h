#pragma once

#include "ViewModelFwd.h"

#include <Model/ModelFwd.h>
#include <RenderApi/RenderApiFwd.h>


class WorldVm
{
public:

  WorldVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController,
    int i_screenWidth, int i_screenHeight);

  ICamera& getCamera() { return *d_camera; }
  const ICamera& getCamera() const { return *d_camera; }

  void buildFromWorld(const World& i_world);

  void render() const;

private:

  IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;

  std::shared_ptr<ICamera> d_camera;
  std::shared_ptr<IRenderer3d> d_renderer;

  std::shared_ptr<TerrainVm> d_terrainVm;
  std::vector<std::shared_ptr<ObjectVm>> d_objectVms;

};
