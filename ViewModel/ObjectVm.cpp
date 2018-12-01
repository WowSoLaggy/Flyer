#include "stdafx.h"
#include "ObjectVm.h"

#include <Model/Object.h>
#include <RenderApi/IRenderer3d.h>
#include <RenderApi/IResourceController.h>
#include <Sdk/Vector.h>


ObjectVm::ObjectVm(const IResourceController& i_resourceController, const Object& i_object)
  : d_object(i_object)
  , d_meshResourceCmoId(i_resourceController.getResourceId(d_object.getModelName()))
{
}


void ObjectVm::update(double i_dt)
{
}

void ObjectVm::render(IRenderer3d& i_renderer) const
{
  i_renderer.renderObject(d_meshResourcCmoId, d_object.getPosition(), d_object.getRotation());
}
