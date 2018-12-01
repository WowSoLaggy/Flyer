#pragma once

#include <Model/ModelFwd.h>
#include <RenderApi/RenderApiFwd.h>
#include <Sdk/SdkFwd.h>


class ObjectVm
{
public:

  ObjectVm(const IResourceController& i_resourceController, const Object& i_object);

  void update(double i_dt);
  void render(IRenderer3d& i_renderer) const;

private:

  const Object& d_object;
  const ResourceId d_meshResourceCmoId;


};
