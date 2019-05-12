#include "stdafx.h"
#include "WorldVm.h"

#include "TerrainVm.h"
#include "ObjectVm.h"

#include <Model/World.h>
#include <ModelControllers/WorldController.h>
#include <ModelControllers/WorldEvents.h>
#include <LaggyDx/IRenderer3d.h>


WorldVm::WorldVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
{
}


void WorldVm::buildFromWorld(WorldController& i_worldController)
{
  auto& worldController = dynamic_cast<WorldController&>(i_worldController);

  d_terrainVm = std::make_shared<TerrainVm>(
    d_renderDevice, d_resourceController, worldController.getWorld().getTerrain());

  for (const auto& object : worldController.getWorld().getObjects())
    onObjectAdded(*object);

  connectTo(worldController);
}


void WorldVm::render(IRenderer3d& i_renderer, double i_dt) const
{
  d_terrainVm->render(i_renderer);

  for (const auto& objectVm : d_objectVms)
  {
    objectVm->update(i_dt);
    objectVm->render(i_renderer);
  }
}


void WorldVm::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* pObjectAddedEvent = dynamic_cast<const ObjectAddedEvent*>(&i_event))
    onObjectAdded(*pObjectAddedEvent->getObject());
  else if (const auto* pObjectDeletedEvent = dynamic_cast<const ObjectDeletedEvent*>(&i_event))
    onObjectDeleted(*pObjectDeletedEvent->getObject());
}


void WorldVm::onObjectAdded(const Object& i_object)
{
  d_objectVms.push_back(std::make_shared<ObjectVm>(d_resourceController, i_object));
}

void WorldVm::onObjectDeleted(const Object& i_object)
{
  d_objectVms.erase(std::remove_if(d_objectVms.begin(), d_objectVms.end(),
                                   [&](std::shared_ptr<ObjectVm> i_objectVm)
  {
    return i_objectVm->getObject().getId() == i_object.getId();
  }), d_objectVms.end());
}
