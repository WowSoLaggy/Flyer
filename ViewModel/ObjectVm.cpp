#include "stdafx.h"
#include "ObjectVm.h"

#include <Model/Object.h>
#include <RenderApi/IResourceController.h>
#include <Sdk/Vector.h>


ObjectVm::ObjectVm(const IResourceController& i_resourceController, const Object& i_object)
  : d_object(i_object)
  , d_meshResourceId(i_resourceController.getResourceId(d_object.getModelName()))
  , d_textureResourceId(i_resourceController.getResourceId(d_object.getTextureName()))
{
}


const Vector3& ObjectVm::getPosition() const
{
  const auto& objectPosition = d_object.getPosition();
  return { objectPosition.x, objectPosition.y, 0 };
}
