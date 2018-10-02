#pragma once

#include <Model/ModelFwd.h>
#include <RenderApi/IObject3d.h>
#include <RenderApi/RenderApiFwd.h>


class ObjectVm : public IObject3d
{
public:

  ObjectVm(const IResourceController& i_resourceController, const Object& i_object);

  virtual ResourceId getMeshResourceId() const override { return d_meshResourceId; }
  virtual ResourceId getTextureResourceId() const override { return d_textureResourceId; }

  virtual Vector3 getPosition() const override;

private:

  const Object& d_object;

  const ResourceId d_meshResourceId;
  const ResourceId d_textureResourceId;
};
