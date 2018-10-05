#pragma once

#include <Model/ModelFwd.h>
#include <RenderApi/RenderApiFwd.h>
#include <Sdk/SdkFwd.h>


class ObjectVm
{
public:

  ObjectVm(const IResourceController& i_resourceController, const Object& i_object);

  ResourceId getMeshResourceId() const { return d_meshResourceId; }
  ResourceId getTextureResourceId() const { return d_textureResourceId; }

  const Vector3& getPosition() const;

private:

  const Object& d_object;

  const ResourceId d_meshResourceId;
  const ResourceId d_textureResourceId;
};
