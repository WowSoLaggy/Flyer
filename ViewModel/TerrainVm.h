#pragma once

#include <Model/ModelFwd.h>
#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/IndexBuffer.h>
#include <LaggyDx/MaterialSequence.h>
#include <LaggyDx/VertexBuffer.h>


class TerrainVm
{
public:

  TerrainVm(
    Dx::IRenderDevice& io_renderDevice, const Dx::IResourceController& i_resourceController,
    const Terrain& i_terrain);
  ~TerrainVm();

  void render(Dx::IRenderer3d& i_renderer) const;

private:

  const Terrain& d_terrain;

  const Dx::ResourceId d_textureResourceId;

  Dx::VertexBuffer d_vertexBuffer;
  Dx::IndexBuffer d_indexBuffer;
  Dx::MaterialSequence d_materialSequence;

  void createBuffers(Dx::IRenderDevice& io_renderDevice);
};
