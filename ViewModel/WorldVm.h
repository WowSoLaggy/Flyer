#pragma once

#include "ViewModelFwd.h"

#include <Model/ModelFwd.h>
#include <ModelControllers/ModelControllersFwd.h>
#include <RenderApi/RenderApiFwd.h>
#include <Sdk/EventHandler.h>


class WorldVm : public EventHandler
{
public:

  WorldVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController);

  void buildFromWorld(WorldWrapper& i_world);

  void render(IRenderer3d& i_renderer, double i_dt) const;

  virtual void processEvent(const IEvent& i_event) override;

private:

  IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;

  std::shared_ptr<TerrainVm> d_terrainVm;
  std::vector<std::shared_ptr<ObjectVm>> d_objectVms;

  void onObjectAdded(const Object& i_object);
  void onObjectDeleted(const Object& i_object);

};
