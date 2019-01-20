#pragma once

#include "RenderApiFwd.h"

#include <Sdk/Vector.h>


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
    ResourceId i_textureResourceId,
    const VertexBuffer& i_vertexBuffer, const IndexBuffer& i_indexBuffer,
    const std::vector<MaterialSpan>& i_materialSpans,
    const Vector3& i_position, const Vector3& i_rotation) = 0;

  virtual void renderObject(ResourceId i_meshResourceCmoId,
    const IAnimationController& i_animationController,
    const Vector3& i_position, const Vector3& i_rotation) = 0;
};
