#include "stdafx.h"
#include "ObjectVm.h"

#include <Model/Object.h>
#include <RenderApi/IRenderer3d.h>
#include <RenderApi/IResourceController.h>
#include <Sdk/Vector.h>


ObjectVm::ObjectVm(const IResourceController& i_resourceController, const Object& i_object)
  : d_object(i_object)
  , d_textureResourceId(i_resourceController.getResourceId(d_object.getTextureName()))
  , d_meshResourceObjId(i_resourceController.getResourceId(d_object.getModelName()))
{
}


void ObjectVm::render(IRenderer3d& i_renderer) const
{
  i_renderer.renderObject(d_textureResourceId, d_meshResourceObjId,
    d_object.getPosition(), d_object.getRotation());
}
