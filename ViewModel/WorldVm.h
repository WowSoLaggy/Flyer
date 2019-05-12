#pragma once

#include "ViewModelFwd.h"

#include <Model/ModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>
#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/EventHandler.h>


class WorldVm : public Sdk::EventHandler
{
public:

  WorldVm(Dx::IRenderDevice& io_renderDevice, const Dx::IResourceController& i_resourceController);

  void buildFromWorld(WorldController& i_worldController);

  void render(Dx::IRenderer3d& i_renderer, double i_dt) const;

  virtual void processEvent(const Sdk::IEvent& i_event) override;

private:

  Dx::IRenderDevice& d_renderDevice;
  const Dx::IResourceController& d_resourceController;

  std::shared_ptr<TerrainVm> d_terrainVm;
  std::vector<std::shared_ptr<ObjectVm>> d_objectVms;

  void onObjectAdded(const Object& i_object);
  void onObjectDeleted(const Object& i_object);

};
