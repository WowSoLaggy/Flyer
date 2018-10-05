#include "stdafx.h"
#include "TerrainVm.h"

#include <Model/Terrain.h>
#include <RenderApi/IResourceController.h>


namespace
{

  Vector3 getPosition() { return { 0, 0, 0 }; }

} // anonymous NS


TerrainVm::TerrainVm(
  IRenderDevice& io_renderDevice, const IResourceController& i_resourceController,
  const Terrain& i_terrain)
  : d_terrain(i_terrain)
  , d_textureResourceId(i_resourceController.getResourceId(d_terrain.getTextureName()))
{
  createBuffers(io_renderDevice);
}

TerrainVm::~TerrainVm()
{
  d_vertexBuffer.dispose();
  d_indexBuffer.dispose();
}


{

void TerrainVm::createBuffers(IRenderDevice& io_renderDevice)
{
  auto& heightMap = d_terrain.getHeightMap();
  float heightGridStep = d_terrain.getHeightGridStep();
  
  int sizeX = heightMap.getSizeX();
  int sizeZ = heightMap.getSizeZ();

  std::vector<VertexTypePosTexNorm> vertices;
  std::vector<int> indices;

  vertices.reserve(sizeX * sizeZ);
  indices.reserve((sizeX - 1) * (sizeZ - 1) * 2);


  auto addVertice = [&](int x, int z)
  {
    Vector3 pos = { x * heightGridStep, heightMap.getHeight(x, z), z * heightGridStep };
    Vector2 uv = { x * heightGridStep, z * heightGridStep };
    Vector3 norm = { 0, 1, 0 };

    vertices.push_back({ pos, uv, norm });
  };

  auto addIndices = [&](int x, int z)
  {
    /**

    We are operating the RH coordinate system (see pic below, Y-axis goes towards us)
    For the following square:

        (0, 0) *---* (1, 0) ----> X-axis
               | \ |
        (0, 1) *---* (1, 1)
               |
               |
               v Z-axis

    We are creating two triangles:
      t1: (0, 0); (1, 0); (1, 1)
      t2: (0, 0); (1, 1); (0, 1)
    
    */

    // t1:
    indices.push_back(x + z * sizeX);
    indices.push_back((x + 1) + z * sizeX);
    indices.push_back((x + 1) + (z + 1) * sizeX);

    // t2:
    indices.push_back(x + z * sizeX);
    indices.push_back((x + 1) + (z + 1) * sizeX);
    indices.push_back(x + (z + 1) * sizeX);
  };


  for (int z = 0; z < sizeZ; ++z)
  {
    for (int x = 0; x < sizeX; ++x)
    {
      addVertice(x, z);

      // Don't add indices for the last row and col because it will be out of bounds
      if (x < sizeX - 1 && z < sizeZ - 1)
        addIndices(x, z);
    }
  }


  d_vertexBuffer.create(io_renderDevice, vertices);
  d_indexBuffer.create(io_renderDevice, indices);

  d_materialSequence.add({ Material::getDefault(), 0, d_indexBuffer.getIndexCount() });
}
