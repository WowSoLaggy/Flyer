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
    ResourceId i_textureResourceId, ResourceId i_meshResourceId,
    const Vector3& i_position) = 0;

  virtual void renderObject(
    ResourceId i_textureResourceId,
    const VertexBuffer& i_vertexBuffer, const IndexBuffer& i_indexBuffer,
    const std::vector<MaterialSpan>& i_materialSpans, const Vector3& i_position) = 0;
};
