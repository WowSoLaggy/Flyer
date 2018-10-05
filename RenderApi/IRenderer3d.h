#pragma once

#include "RenderApiFwd.h"

#include <Sdk/SdkFwd.h>


class IRenderer3d
{
public:

  static std::shared_ptr<IRenderer3d> create(
    IRenderDevice& io_renderDevice,
    const IResourceController& i_resourceController,
    const ICamera& i_camera);

public:

  virtual ~IRenderer3d() = default;

  virtual void beginScene() = 0;
  virtual void endScene() = 0;

  virtual void renderObject(
    ResourceId i_meshResourceId, ResourceId i_textureResourceId,
    const Vector3& i_position) = 0;
};
