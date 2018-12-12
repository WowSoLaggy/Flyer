#include "stdafx.h"
#include "WorldVm.h"

#include "TerrainVm.h"
#include "ObjectVm.h"

#include <ModelControllers/WorldEvents.h>
#include <ModelControllers/WorldWrapper.h>
#include <RenderApi/IRenderer3d.h>


WorldVm::WorldVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
{
}


void WorldVm::buildFromWorld(WorldWrapper& i_world)
{
  d_terrainVm = std::shared_ptr<TerrainVm>(
    new TerrainVm(d_renderDevice, d_resourceController, i_world.getTerrain()));

  for (const auto& object : i_world.getObjects())
    onObjectAdded(*object);

  connectTo(i_world);
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


void WorldVm::processEvent(const IEvent& i_event)
{
  if (const auto* pObjectAddedEvent = dynamic_cast<const ObjectAddedEvent*>(&i_event))
    onObjectAdded(pObjectAddedEvent->getObject());
  else if (const auto* pObjectDeletedEvent = dynamic_cast<const ObjectDeletedEvent*>(&i_event))
    onObjectDeleted(pObjectDeletedEvent->getObject());
}


void WorldVm::onObjectAdded(const Object& i_object)
{
  d_objectVms.push_back(std::make_shared<ObjectVm>(d_resourceController, i_object));
}

void WorldVm::onObjectDeleted(const Object& i_object)
{
  d_objectVms.erase(std::remove_if(d_objectVms.begin(), d_objectVms.end(),
    [&](const std::shared_ptr<ObjectVm>& i_objectVm)
  {
    return i_objectVm->getObject().getId() == i_object.getId();
  }), d_objectVms.end());
}
