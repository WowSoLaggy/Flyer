#pragma once

#include <Model/ModelFwd.h>
#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/SdkFwd.h>


class ObjectVm
{
public:

  ObjectVm(const IResourceController& i_resourceController, const Object& i_object);

  void update(double i_dt);
  void render(IRenderer3d& i_renderer) const;

  const Object& getObject() const { return d_object; }

private:

  const Object& d_object;
  const ResourceId d_meshResourceCmoId;

  std::shared_ptr<IAnimationController> d_animationController;

};
