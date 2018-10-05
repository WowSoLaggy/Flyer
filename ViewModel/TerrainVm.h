#pragma once

#include <Model/ModelFwd.h>
#include <RenderApi/RenderApiFwd.h>
#include <RenderApi/IndexBuffer.h>
#include <RenderApi/MaterialSequence.h>
#include <RenderApi/VertexBuffer.h>


class TerrainVm
{
public:

  TerrainVm(
    IRenderDevice& io_renderDevice, const IResourceController& i_resourceController,
    const Terrain& i_terrain);
  ~TerrainVm();

  void render(IRenderer3d& i_renderer) const;

private:

  const Terrain& d_terrain;

  const ResourceId d_textureResourceId;

  VertexBuffer d_vertexBuffer;
  IndexBuffer d_indexBuffer;
  MaterialSequence d_materialSequence;

  void createBuffers(IRenderDevice& io_renderDevice);
};
