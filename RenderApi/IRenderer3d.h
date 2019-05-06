#pragma once

#include "IRenderer.h"
#include "RenderApiFwd.h"

#include <LaggySdk/Vector.h>


class IRenderer3d : public IRenderer
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
    const Sdk::Vector3& i_position, const Sdk::Vector3& i_rotation) = 0;

  virtual void renderObject(
    ResourceId i_meshResourceCmoId, ResourceId i_textureResourceId,
    std::shared_ptr<IAnimationController> i_animationController,
    const Sdk::Vector3& i_position, const Sdk::Vector3& i_rotation, const Sdk::Vector3& i_scale,
    bool i_useLighting) = 0;
};
